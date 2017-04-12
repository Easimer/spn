#include <SDL2/SDL.h>
#include "renderer.hpp"

SDL2Renderer::SDL2Renderer() : SDL2Renderer(1280, 720) {}

SDL2Renderer::SDL2Renderer(unsigned int width, unsigned int height)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &(this->window), &(this->renderer));
	SDL_RenderClear(this->renderer);
}

SDL2Renderer::~SDL2Renderer()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void SDL2Renderer::Clear()
{
	SDL_RenderClear(this->renderer);
}

void SDL2Renderer::Present()
{
	SDL_RenderPresent(this->renderer);
}
