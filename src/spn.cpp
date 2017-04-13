#include <iostream>

#include "renderer.hpp"
#include "scene.hpp"

int main(int argc, char** argv)
{
	SDL2Renderer r(1920, 1080);
	TestScene ts(r);
	while(!r.IsQuit())
	{
		r.Clear();
		r.Update();
		ts.Draw();
		r.Present();
	}
	return 0;
}
