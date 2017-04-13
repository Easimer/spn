#include "renderer.hpp"
#include <iostream>
#include <SDL2/SDL.h>

SDL2Renderer::SDL2Renderer() : SDL2Renderer(1280, 720) {}

SDL2Renderer::SDL2Renderer(unsigned int width, unsigned int height)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &(this->window), &(this->renderer));
	SDL_RenderClear(renderer);
	this->width = width; this->height = height;
	//IMG_Init(IMG_INIT_PNG);
	last_frame = std::chrono::high_resolution_clock::now();
}

unsigned SDL2Renderer::GetWidth(void)
{
	return width;
}

unsigned SDL2Renderer::GetHeight(void)
{
	return height;
}

SDL2Renderer::~SDL2Renderer()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "SDL_Quit" << std::endl;
}

void SDL2Renderer::Clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void SDL2Renderer::Present()
{
	SDL_RenderPresent(renderer);
	/*auto now = std::chrono::high_resolution_clock::now();
	std::cout << "Render time: " << std::chrono::duration_cast<std::chrono::milliseconds>(now - last_frame).count() << " milliseconds" << std::endl;
	clock = std::chrono::high_resolution_clock::now();*/

	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_frame).count();
	std::cout << "Render time: " << duration << " milliseconds" << std::endl;
	last_frame = now;
}

void SDL2Renderer::SetColor(Vector3& color)
{
	//std::cout << "SC: (" << color[0] << ',' << color[1] << ',' << color[2] << ')' << std::endl;
	SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
}

void SDL2Renderer::SetColor(double r, double g, double b)
{
	//std::cout << "SC: (" << r << ',' << g << ',' << b << ')' << std::endl;
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void SDL2Renderer::PlotPixel(unsigned x, unsigned y)
{
	//std::cout << "PP: (" << x << ',' << y << ')' << std::endl;
	SDL_RenderDrawPoint(renderer, x, y);
}

void SDL2Renderer::Update(void)
{
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
				break;
			default:
				//std::cout << "unk ev" << std::endl;
				break;
		}
	}
	
}
