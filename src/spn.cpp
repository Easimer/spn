#include "spn.hpp"
#include <iostream>
#include "scene.hpp"
#include "renderer.hpp"

int main(int argc, char** argv)
{
	SDL2Renderer r(1280, 720);
	TestScene ts(r);
	while(!r.IsQuit())
	{
		r.Clear();
		ts.Update();
		ts.Draw();
		r.Present();
	}
	return 0;
}
