#include <iostream>

#include "renderer.hpp"
#include "scene.hpp"

int main(int argc, char** argv)
{
	SDL2Renderer r(1280, 720);
	TestScene ts(r);
	ts.Draw();
	return 0;
}
