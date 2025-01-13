#include <iostream>
#include "Graph.h"
#include "GraphLoader.h"
#include "GraphPrinter.hpp"
#include "Basis.h"
#include "Mouse.h"
#include "RenderMisc.h"

#include <SDL.h>
#include <SDL_ttf.h>

bool init();
void kill();
bool loop();
bool process_events();

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;

Basis basis(WINDOW_WIDTH, WINDOW_HEIGHT);
Mouse mouse;

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

	window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

	font = TTF_OpenFont("CascadiaCode.ttf", 50);
	if (!font) {
		std::cout << "Error loading font: " << TTF_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	return true;
}


bool loop()
{
	if (!process_events()) {
		return false;
	}

	// Clear the window to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// Set drawing color to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	render_circle(renderer, basis.loc_to_window_x(0), basis.loc_to_window_y(0), 25.0 * basis.get_scale());
	render_circle(renderer, basis.loc_to_window_x(200), basis.loc_to_window_y(150), 15.0 * basis.get_scale());

	render_text(renderer, font, std::to_string(basis.get_scale()), 10, 10);
	render_text(renderer, font, "x: " + std::to_string(mouse.x), 10, 60);
	render_text(renderer, font, "y: " + std::to_string(mouse.y), 10, 110);
	render_text(renderer, font, "local x: " + std::to_string(basis.window_to_loc_x(mouse.x)), 10, 160);
	render_text(renderer, font, "local y: " + std::to_string(basis.window_to_loc_y(mouse.y)), 10, 210);

	SDL_RenderPresent(renderer);

	return true;
}

bool process_events()
{
	SDL_Event e;

	// Event loop
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case SDL_QUIT:
			return false;
		case SDL_MOUSEMOTION:
			mouse.x = e.button.x;
			mouse.y = e.button.y;
			break;
		case SDL_MOUSEWHEEL:
			if (e.wheel.y > 0) {
				basis.scale_up(mouse.x, mouse.y);
			}
			else {
				basis.scale_down(mouse.x, mouse.y);
			}
		}
	}

	return true;
}


void kill() {
	// Quit
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