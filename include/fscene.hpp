#pragma once
#include "scene.hpp"

class FileScene : public Scene {
public:
	FileScene(std::string filename, Renderer&r);
	void Update(double dt);
	void Draw(void);

protected:
	void ProcessFile(void);

private:
	std::string filename;
};
