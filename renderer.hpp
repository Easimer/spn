#pragma once

#include <SDL2/SDL.h>
#include "vec.hpp"

class Renderer {
public:
	virtual unsigned GetWidth() {return 0;};
	virtual unsigned GetHeight()  {return 0;};

	virtual void SetColor(Vector3& color) {};
	virtual void SetColor(double r, double g, double b) {};
	virtual void PlotPixel(unsigned x, unsigned y) {};
	virtual void Clear(void) {};
	virtual void Present(void) {};
};

class SDL2Renderer : public Renderer {
public:
	SDL2Renderer();
	SDL2Renderer(unsigned int width, unsigned int height);
	~SDL2Renderer();

	unsigned GetWidth();
	unsigned GetHeight();

	void SetColor(Vector3& color);
	void SetColor(double r, double g, double b);
	void PlotPixel(unsigned x, unsigned y);

	void Clear(void);
	void Present(void);
private:
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Window* window;
	unsigned width, height;
};

