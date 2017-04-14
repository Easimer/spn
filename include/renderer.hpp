#pragma once

#include <SDL2/SDL.h>
#include <chrono>
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
	virtual void Update(void) {};

protected:
	bool quit = false;
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
	void Update(void);

	unsigned GetDelta(void);

	bool SaveFrame(std::string filepath);

	bool IsQuit() { return quit; };
private:
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Window* window;
	unsigned width, height;
	bool quit = false;
	std::chrono::time_point<std::chrono::high_resolution_clock> last_frame;
	unsigned delta_time;
	unsigned frame_counter = 0;
};

