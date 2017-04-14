#include "spn.hpp"
#include <iostream>
#include "fscene.hpp"
#include "renderer.hpp"
#include "scripting.hpp"

int main(int argc, char** argv)
{
	if(argc < 2)
		return 1;
	SDL2Renderer r(1280, 720);
	FileScene ts(std::string(argv[1]), r);
	ScriptingContext sc(ts);
	while(!r.IsQuit())
	{
		r.Clear();
		r.Update();
		double dt = (double)r.GetDelta() / 1000.0;
		ts.Update(dt);
		sc.Update(dt);
		ts.Draw();
		r.Present();
	}
	return 0;
}
