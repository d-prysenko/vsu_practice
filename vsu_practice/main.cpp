// Подключение заголовочных файлов
#include <iostream>
#include "Graph.h"
#include "GraphLoader.h"
#include "GraphPrinter.hpp"

#include <SDL.h>
#include <SDL_ttf.h>

// You shouldn't really use this statement, but it's fine for small programs
using namespace std;

bool init();
void kill();
bool loop();

// Pointers to our window and renderer
SDL_Window* window;
SDL_Renderer* renderer;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;

TTF_Font* font;

int main(int argc, char** args) {

	if (!init()) return 1;

	while (loop()) {
		// wait before processing the next frame
		SDL_Delay(10);
	}

	kill();
	return 0;
}

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}


float scaleFactor = 1.0f;
const float scaleAmount = 1.3f;
static int mx0 = -1, my0 = -1, mx1 = -1, my1 = -1;

int centerTransX = 0;
int centerTransY = 0;

float loc_to_window_x(float loc_x)
{
	return (WINDOW_WIDTH / 2) + scaleFactor * (loc_x + centerTransX);
}

float loc_to_window_y(float loc_y)
{
	return (WINDOW_HEIGHT / 2) - scaleFactor * (loc_y + centerTransY);
}

float window_to_loc_x(float window_x)
{
	return (window_x - (WINDOW_WIDTH / 2)) / scaleFactor - centerTransX;
}

float window_to_loc_y(float window_y)
{
	return ((WINDOW_HEIGHT / 2) - window_y ) / scaleFactor - centerTransY;
}

float calc_x_trans_for_new_scale(float loc_x, float window_x)
{
	return (window_x - (WINDOW_WIDTH / 2)) / scaleFactor - loc_x;
}

float calc_y_trans_for_new_scale(float loc_y, float window_y)
{
	return ((WINDOW_HEIGHT / 2) - window_y) / scaleFactor - loc_y;
}

void scaleUp()
{
	float x = window_to_loc_x(mx1);
	float y = window_to_loc_y(my1);

	scaleFactor *= scaleAmount;

	centerTransX = calc_x_trans_for_new_scale(x, mx1);
	centerTransY = calc_y_trans_for_new_scale(y, my1);
}

void scaleDown()
{
	if (scaleFactor > 0)
	{
		float x = window_to_loc_x(mx1);
		float y = window_to_loc_y(my1);

		scaleFactor /= scaleAmount;

		centerTransX = calc_x_trans_for_new_scale(x, mx1);
		centerTransY = calc_y_trans_for_new_scale(y, my1);
	}
}



void render_text(std::string str, int x, int y)
{
	SDL_Rect dest;
	SDL_Color foreground = { 0, 0, 0 };
	SDL_Surface* text_surf = TTF_RenderText_Solid(font, str.c_str(), foreground);

	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, text_surf);

	dest.x = x;
	dest.y = y;
	dest.w = text_surf->w;
	dest.h = text_surf->h;
	SDL_RenderCopy(renderer, text, NULL, &dest);

	SDL_DestroyTexture(text);
	SDL_FreeSurface(text_surf);
}

bool loop() {

	static const unsigned char* keys = SDL_GetKeyboardState(NULL);

	SDL_Event e;
	SDL_Rect r;
	// For mouse rectangle (static to presist between function calls)
	

	// Clear the window to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// Event loop
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case SDL_QUIT:
			return false;
		case SDL_MOUSEBUTTONDOWN:
			mx0 = e.button.x;
			my0 = e.button.y;
			break;
		case SDL_MOUSEMOTION:
			mx1 = e.button.x;
			my1 = e.button.y;
			break;
		case SDL_MOUSEBUTTONUP:
			mx0 = my0 = mx1 = my1 = -1;
			break;
		case SDL_MOUSEWHEEL:
			//render_text(std::to_string(e.wheel.y), 500, 10);
			if (e.wheel.y > 0) {
				scaleUp();
			}
			else {
				scaleDown();
			}
		}
	}

	// Set drawing color to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Test key states - this could also be done with events
	if (keys[SDL_SCANCODE_1]) {
		//SDL_RenderDrawPoint(renderer, 10, 10);
		scaleUp();
		
	}
	if (keys[SDL_SCANCODE_2]) {
		//SDL_RenderDrawLine(renderer, 10, 20, 10, 100);
		scaleDown();
		
	}
	if (keys[SDL_SCANCODE_3]) {
		r.x = 20;
		r.y = 20;
		r.w = 100;
		r.h = 100;
		SDL_RenderFillRect(renderer, &r);
	}

	DrawCircle(renderer, loc_to_window_x(0), loc_to_window_y(0), 25.0 * scaleFactor);
	DrawCircle(renderer, loc_to_window_x(200), loc_to_window_y(150), 15.0 * scaleFactor);
	//DrawCircle(renderer, to_window_x(trans_loc_x(100, 50)), to_window_y(trans_loc_y(100, 50)), 15 * scaleFactor);

	//DrawCircle(renderer, translate_x(to_window_x(0)), translate_y(to_window_y(0)), 25 * scaleFactor);
	//DrawCircle(renderer, translate_x(to_window_x(-150)), translate_y(to_window_y(150)), 15 * scaleFactor);
	//DrawCircle(renderer, translate_x(to_window_x(100)), translate_y(to_window_y(50)), 15 * scaleFactor);

	// Render mouse rectangle
	if (mx0 != -1) {
		r.x = mx0;
		r.y = my0;
		r.w = mx1 - mx0;
		r.h = my1 - my0;
		//SDL_RenderDrawRect(renderer, &r);

		//DrawCircle(renderer, mx0, my0, sqrt((mx1 - mx0)* (mx1 - mx0) + (my1 - my0) * (my1 - my0)));

	}

	render_text(std::to_string(scaleFactor), 10, 10);
	render_text("x: " + std::to_string(mx1), 10, 60);
	render_text("y: " + std::to_string(my1), 10, 110);
	render_text("local x: " + std::to_string(window_to_loc_x(mx1)), 10, 160);
	render_text("local y: " + std::to_string(window_to_loc_y(my1)), 10, 210);


	// Update window
	SDL_RenderPresent(renderer);

	return true;
}



bool init() {
	// See last example for comments
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
		return false;
	}

	if (TTF_Init() < 0) {
		cout << "Error initializing SDL_ttf: " << TTF_GetError() << endl;
	}

	window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		cout << "Error creating window: " << SDL_GetError() << endl;
		system("pause");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		cout << "Error creating renderer: " << SDL_GetError() << endl;
		return false;
	}

	// Load font
	font = TTF_OpenFont("CascadiaCode.ttf", 50);
	if (!font) {
		cout << "Error loading font: " << TTF_GetError() << endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
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