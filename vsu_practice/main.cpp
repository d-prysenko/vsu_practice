#include <iostream>
#include <vector>
#include <format>
#include "graph/Graph.h"
#include "graph/GraphLoader.h"
#include "graph/GraphPrinter.hpp"
#include "Basis.h"
#include "Mouse.h"
#include "gui/GraphView.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "imgui_stdlib.h"

#include "gui/RenderMisc.h"
#include "gui/ImguiVertexAddingPopup.h"

#include <SDL.h>
#include <SDL_ttf.h>



bool init();
void kill();
bool loop();
bool process_events();

void on_mouse_wheel(const SDL_Event& e);
void on_mouse_motion(const SDL_Event& e);
void on_mouse_button_down(const SDL_Event& e);

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
TTF_Font* font_small;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;


Graph graph;
GraphView graphView;

Basis basis(WINDOW_WIDTH, WINDOW_HEIGHT);
Mouse mouse;

ImguiVertexAddingPopup vertexPopup;

ImGuiIO* io;

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

std::string distance = "";
std::string path = "";



int main(int argc, char** args) {

	if (!init()) {
		return 1;
	}

	while (loop()) {
		// wait before processing the next frame
		SDL_Delay(10);
	}

	kill();

	return 0;
}


bool init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	if (TTF_Init() < 0) {
		std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
	}

	window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!window) {
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	font = TTF_OpenFont("res/CascadiaCode.ttf", 40);
	if (!font) {
		std::cout << "Error loading font: " << TTF_GetError() << std::endl;
		return false;
	}

	font_small = TTF_OpenFont("res/CascadiaCode.ttf", 22);
	if (!font_small) {
		std::cout << "Error loading font: " << TTF_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	graph.addVertex("a");
	graphView.addVertexDraft(0, 0);
	graphView.commitVertexDraft("a");
	graphView.unselectAll();

	graph.addVertex("b");
	graphView.addVertexDraft(200, 300);
	graphView.commitVertexDraft("b");
	graphView.unselectAll();

	graph.addRelation("a", "b", 10);
	graphView.addEdge(0, 1, 10);

	return true;
}


void imgui_vertex_popup_confirm(std::string name, std::string weight, bool biderectional)
{
	int selected = graphView.selected;
	int previousSelected = graphView.previousSelected;

	graphView.unselectAll();

	if (selected >= 0)
	{
		if (graphView.hasVertexDraft()) {
			graphView.commitVertexDraft(name);
			graph.addVertex(name);
		}

		if (previousSelected >= 0) {
			graphView.addEdge(previousSelected, selected, std::stof(weight));
			graph.addRelation(graphView.getCircles()[previousSelected]->name, graphView.getCircles()[selected]->name, std::stof(weight));
		}
	}
}

void imgui_vertex_popup_close()
{
	graphView.unselectAll();

	if (graphView.hasVertexDraft()) {
		graphView.removeVertexDraft();
	}
}

bool loop()
{
	if (!process_events()) {
		return false;
	}


	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	vertexPopup.render(graphView.previousSelected >= 0, imgui_vertex_popup_close, imgui_vertex_popup_confirm);

	// Clear the window to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// Set drawing color to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	for (const Circle* circle : graphView.getCircles())
	{
		render_circle(renderer, basis.loc_to_window_x(circle->x), basis.loc_to_window_y(circle->y), circle->radius * basis.get_scale());
		render_text(renderer, font_small, circle->name, basis.loc_to_window_x(circle->x), basis.loc_to_window_y(circle->y), true);
	}

	for (const Edge& edge : graphView.getEdges())
	{
		SDL_Rect rect;
		rect.x = basis.loc_to_window_x(edge.line.x2 - 5);
		rect.y = basis.loc_to_window_y(edge.line.y2 + 5);
		rect.w = basis.get_scale() * 10.0;
		rect.h = basis.get_scale() * 10.0;

		SDL_RenderDrawLine(
			renderer,
			basis.loc_to_window_x(edge.line.x1), basis.loc_to_window_y(edge.line.y1),
			basis.loc_to_window_x(edge.line.x2), basis.loc_to_window_y(edge.line.y2)
		);
		SDL_RenderFillRect(
			renderer,
			&rect
		);

		render_text(renderer,
			font_small,
			std::format("{:.1f}", edge.weight),
			basis.loc_to_window_x((edge.line.x1 + edge.line.x2) / 2.0),
			basis.loc_to_window_y((edge.line.y1 + edge.line.y2) / 2.0)
		);
	}

	render_text(renderer, font, std::to_string(basis.get_scale()), 10, 10);
	render_text(renderer, font, "x: " + std::to_string(mouse.x), 10, 10 + 40 * 1);
	render_text(renderer, font, "y: " + std::to_string(mouse.y), 10, 10 + 40 * 2);
	render_text(renderer, font, "local x: " + std::to_string(basis.window_to_loc_x(mouse.x)), 10, 10 + 40 * 3);
	render_text(renderer, font, "local y: " + std::to_string(basis.window_to_loc_y(mouse.y)), 10, 10 + 40 * 4);
	render_text(renderer, font, distance, 10, 10 + 40 * 5);
	render_text(renderer, font, path, 10, 10 + 40 * 6);

	if (graphView.selected >= 0)
	{
		render_text(
			renderer,
			font,
			"selected: " +
			(graphView.previousSelected >= 0 ?
				graphView.getPreviousSelectedCircle()->name + "-" :
				"") + graphView.getSelectedCircle()->name,
			10, 940
		);
	}

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
	SDL_RenderPresent(renderer);

	return true;
}

void on_left_mouse_button_down()
{
	if (vertexPopup.opened()) {
		return;
	}

	int i = graphView.getCircleOnCoords(basis.window_to_loc_x(mouse.x), basis.window_to_loc_y(mouse.y));

	if (i >= 0) {
		graphView.select(i);
	}
	else {
		graphView.select(i, false);
	}

	if (graphView.selected >= 0 && graphView.selected == graphView.previousSelected) {
		return;
	}

	if (graphView.selected >= 0 && graphView.previousSelected < 0) {
		return;
	}

	if (graphView.hasEdge(graphView.previousSelected, graphView.selected)) {
		graphView.unselectAll();
		return;
	}

	vertexPopup.open();

	if (graphView.selected < 0)
	{
		graphView.addVertexDraft(basis.window_to_loc_x(mouse.x), basis.window_to_loc_y(mouse.y));
	}
}

template <typename Range, typename Value = typename Range::value_type>
std::string join(Range const& elements, const char* const delimiter) {
	std::ostringstream os;
	auto b = begin(elements), e = end(elements);

	if (b != e) {
		std::copy(b, prev(e), std::ostream_iterator<Value>(os, delimiter));
		b = prev(e);
	}
	if (b != e) {
		os << *b;
	}

	return os.str();
}

void on_right_mouse_button_down()
{
	int i = graphView.getCircleOnCoords(basis.window_to_loc_x(mouse.x), basis.window_to_loc_y(mouse.y));

	if (i < 0) {
		graphView.unselectAll();
		return;
	}

	graphView.select(i);

	if (graphView.selected >= 0 && graphView.selected == graphView.previousSelected) {
		return;
	}

	if (graphView.selected >= 0 && graphView.previousSelected < 0) {
		return;
	}

	std::string src = graphView.getPreviousSelectedCircle()->name;
	std::string dest = graphView.getSelectedCircle()->name;

	VertexTrace res = graph.getDistanceTo(src, dest);
	if (res.distance != FLT_MAX) {
		distance = std::format("p({}, {}) = {:.1f}", src, dest, res.distance);
		
		path = src + " -> " + join(res.path, " -> ");
	}
	else {
		distance = std::format("There is no path for ({}, {})", src, dest);
		path = "";
	}

	printf("%s\n", distance.c_str());

	graphView.unselectAll();
}

bool process_events()
{
	SDL_Event e;

	// Event loop
	while (SDL_PollEvent(&e) != 0) {
		ImGui_ImplSDL2_ProcessEvent(&e);

		switch (e.type) {
		case SDL_QUIT:
			return false;
		case SDL_MOUSEBUTTONDOWN:
			on_mouse_button_down(e);
			break;
		case SDL_MOUSEMOTION:
			on_mouse_motion(e);
			break;
		case SDL_MOUSEWHEEL:
			on_mouse_wheel(e);
		}
	}

	return true;
}

void on_mouse_wheel(const SDL_Event& e)
{
	if (e.wheel.y > 0) {
		basis.scale_up(mouse.x, mouse.y);
		TTF_SetFontSize(font_small, 22 * basis.get_scale());
	}
	else {
		basis.scale_down(mouse.x, mouse.y);
		TTF_SetFontSize(font_small, 22 * basis.get_scale());
	}
}

void on_mouse_motion(const SDL_Event& e)
{
	mouse.x = e.button.x;
	mouse.y = e.button.y;
}

void on_mouse_button_down(const SDL_Event& e)
{
	if (e.button.button == 1) {
		on_left_mouse_button_down();
	}
	else if (e.button.button == 3) {
		on_right_mouse_button_down();
	}
}


void kill() {
	// Quit
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	TTF_CloseFont(font_small);
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



/*

int main()
{
	setlocale(LC_ALL, "ru");

	Graph g;

	try {
		g = GraphLoader::fromFileAsVertexList("graph1.txt");
	}
	catch (std::exception e) {
		fprintf(stderr, e.what());

		system("pause");
		return -1;
	}

	GraphPrinter gp(g);

	gp.printRadius();
	gp.printDiameter();

	gp.printCentralVertices();
	gp.printPeripheralVertices();

	AdjacencyMatrix2 m;


	m.addRelation("a", "b", 1);
	m.addRelation("b", "c", 2);
	m.addRelation("c", "d", 2);
	m.addRelation("c", "e", 4);
	m.addRelation("d", "b", 1);
	m.addRelation("d", "c", 3);
	m.addRelation("e", "d", 5);

	system("pause");
	return 0;
}

*/