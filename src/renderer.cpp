#include "renderer.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL2Renderer::SDL2Renderer() : SDL2Renderer(1280, 720) {}

SDL2Renderer::SDL2Renderer(unsigned int width, unsigned int height)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &(this->window), &(this->renderer));
	SDL_RenderClear(renderer);
	this->width = width; this->height = height;

	if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "SDL_Image init failed" << std::endl;
	}

	last_frame = std::chrono::high_resolution_clock::now();
	delta_time = 0;
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
	IMG_Quit();
	SDL_Quit();
	std::cout << "SDL_Quit" << std::endl;
	std::cout << "Average FPS: " << ((float)frame_counter / (float)elapsed) * 1000 << std::endl;
}

void SDL2Renderer::Clear()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}

void SDL2Renderer::Present()
{
	SDL_RenderPresent(renderer);

	//SaveFrame(std::string("out/frame") + std::to_string(frame_counter) + std::string(".bmp"));
	/*auto now = std::chrono::high_resolution_clock::now();
	std::cout << "Render time: " << std::chrono::duration_cast<std::chrono::milliseconds>(now - last_frame).count() << " milliseconds" << std::endl;
	clock = std::chrono::high_resolution_clock::now();*/

	auto now = std::chrono::high_resolution_clock::now();
	delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_frame).count();
	//std::cout << "Render time: " << delta_time << " milliseconds" << std::endl;
	last_frame = now;
	if(delta_time < 17)
	{
		SDL_Delay((int)(16.66666666666 - delta_time));
	}
	elapsed += delta_time;
	frame_counter++;
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

bool SDL2Renderer::SaveFrame(std::string filepath) {
    SDL_Surface* saveSurface = NULL;
    SDL_Surface* infoSurface = NULL;
    infoSurface = SDL_GetWindowSurface(window);
    if (infoSurface == NULL) {
        std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n";
    } else {
        unsigned char * pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
        if (pixels == 0) {
            std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n";
            return false;
        } else {
            if (SDL_RenderReadPixels(renderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
                std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << "\n";
                pixels = NULL;
                return false;
            } else {
                saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
                if (saveSurface == NULL) {
                    std::cerr << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << "\n";
                    return false;
                }
                SDL_SaveBMP(saveSurface, filepath.c_str());
                SDL_FreeSurface(saveSurface);
                saveSurface = NULL;
            }
            delete[] pixels;
        }
        SDL_FreeSurface(infoSurface);
        infoSurface = NULL;
    }
    return true;
}

unsigned SDL2Renderer::GetDelta(void)
{
	return delta_time;
}

Texture::Texture(unsigned w, unsigned h, void* d)
{
	data = malloc(w * h * 3);
	memcpy(data, d, w * h * 3);
	width = w;
	height = h;
}

Texture::~Texture()
{
	free(data);
}

Vector3 Texture::GetPixel(unsigned x, unsigned y)
{
	uint8_t* pix = (uint8_t*)data;
	unsigned index = y * width + x;
	return Vector3 (pix[index] / 255.0, pix[index+1] / 255.0, pix[index+2] / 255.0);
}
