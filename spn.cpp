#include <iostream>

#include "renderer.hpp"
#include "scene.hpp"

int main(int argc, char** argv)
{
	SDL2Renderer r(1280, 720);
	TestScene ts(r);
	//while(true)
	{
		r.Clear();
		ts.Draw();
		r.Present();
	}
	std::cout << "Press enter to exit" << std::endl;
	system("read");
	return 0;
}
