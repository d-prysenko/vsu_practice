#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

void render_circle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
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

void render_text(SDL_Renderer* renderer, TTF_Font* font, std::string str, int x, int y)
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