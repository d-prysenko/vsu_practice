// Подключение заголовочных файлов
#include <iostream>
#include "Graph.h"
#include "GraphLoader.h"
#include "GraphPrinter.hpp"

#include <SDL.h>

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
static int mx0 = -1, my0 = -1, mx1 = -1, my1 = -1;

int posScaleX = (WINDOW_WIDTH / 2);
int posScaleY = (WINDOW_HEIGHT / 2);

//int to_abs_x(int x)
//{
//	//return (WINDOW_WIDTH / 2) + x * scaleFactor;
//	return posScaleX + (x - posScaleX) * scaleFactor;
//}
//
//int to_abs_y(int y)
//{
//	//return (WINDOW_HEIGHT/ 2) - y * scaleFactor;
//	return posScaleY + (y - posScaleY) * scaleFactor;
//}

int to_window_x(int x)
{
	return (WINDOW_WIDTH / 2) + x;
	return x;
}

int to_window_y(int y)
{
	return (WINDOW_HEIGHT/ 2) - y;
	return y;
}

int to_loc_x(int x)
{
	return (x - (WINDOW_WIDTH / 2));
}

int to_loc_y(int y)
{
	return ((WINDOW_HEIGHT / 2) - y) / scaleFactor;
}

int centerTransX = 0;
int centerTransY = 0;

int trans_loc_x(int x)
{
	return scaleFactor * x + centerTransX;
	//return to_loc_x(posScaleX) + (x - to_loc_x(posScaleX)) * scaleFactor;
	//     -5000               + (50 + 5000) * 0.2
}

int trans_loc_y(int y)
{
	return scaleFactor * y + centerTransY;
	//return to_loc_y(posScaleY) + (y - to_loc_y(posScaleY)) * scaleFactor;
}

//int translate_x(int x)
//{
//	return posScaleX + (x - posScaleX) * scaleFactor;
//}
//
//int translate_y(int y)
//{
//	return posScaleY + (y - posScaleY) * scaleFactor;
//}

void calcCenterTranslate(float t)
{
	centerTransX += (to_loc_x(mx1) - to_loc_x(mx1) * t);
	//centerTransY += (to_loc_y(my1) - centerTransY) * scaleFactor;
}

float oldScale = scaleFactor;

void scaleUp()
{
	oldScale = scaleFactor;
	scaleFactor += 0.005f;
	calcCenterTranslate(oldScale/scaleFactor);
}

void scaleDown()
{
	if (scaleFactor > 0)
	{
		oldScale = scaleFactor;
		scaleFactor -= 0.005f;
	}
	calcCenterTranslate(oldScale / scaleFactor);
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

	DrawCircle(renderer, to_window_x(trans_loc_x(0)), to_window_y(trans_loc_y(0)), 25 * scaleFactor);
	//DrawCircle(renderer, to_window_x(trans_loc_x(-150, 150)), to_window_y(trans_loc_y(-150, 150)), 15 * scaleFactor);
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