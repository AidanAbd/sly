#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <random>

#include <SDL.h>

#include "../lib/SLY.hpp"

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(-10, 10);

int width = 1200;
int height = 1200;

void drawfern(int x, int y, int l, int arg, int n, int perm)
{
	int x1, y1, i;
	int l1, xpt, ypt;

	if (n > 0)
	{
		x1 = (int)(x - l * sin(arg * 3.14 / 180));
		y1 = (int)(y - l * cos(arg * 3.14 / 180));
		std::cout << x << " " << y << " " << x1 << " " << y1 << std::endl;

		SDL_RenderDrawLine(sly::base::renderer, x, y, x1, y1);
		l1 = (int)(l / 5);
		for (i = 1; i < 6; i++)
		{
			xpt = (int)(x - i * l1 * sin(arg * 3.14 / 180));
			ypt = (int)(y - i * l1 * cos(arg * 3.14 / 180));
			drawfern(xpt, ypt, (int)(l / (i + 1)), arg + perm + distribution(generator), n - 1, perm + distribution(generator));
			drawfern(xpt, ypt, (int)(l / (i + 1)), arg - perm - distribution(generator), n - 1, perm + distribution(generator));
		}
	}
}

int main()
{
	puts("Loading: SLY Fern application");
	sly::base::init("SLY Fern app", 1000, 1000);
	SDL_SetRenderDrawColor(sly::base::renderer, 0x00, 0x2F, 0xA7, 0xFF);
	SDL_RenderClear(sly::base::renderer);
	SDL_SetRenderDrawColor(sly::base::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	int x, y, l, a;
	x = 850;
	y = 1100;
	l = 1000;
	a = 30;
	drawfern(x, y, l, 30, 7, a);

	sly::base::render();

	SDL_Event event;
	bool running = true;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			running = true;
		}
	}

	return 0;
}
