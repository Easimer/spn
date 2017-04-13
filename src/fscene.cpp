#include "fscene.hpp"
#include "scene.hpp"
#include <fstream>

// FileScene - scene loaded from file

FileScene::FileScene(std::string filename, Renderer& r) : Scene::Scene(r)
{
	this->filename = filename;
	ProcessFile();
}

void FileScene::ProcessFile(void)
{
	std::ifstream file(filename, std::ios::in);

	std::string line;
	std::string token;
	std::string type;
	double a, b, c, d, e, f, g;
	int i;

	std::string light("light");
	std::string sphere("sphere");

	while(!file.eof())
	{
		std::getline(file, line);

		if(line.size() == 0)
			break;
		
		// entity type
		i = line.find(" ");
		token = line.substr(0, i);
		line.erase(0, i + 1);
		type = token;

		// a
		i = line.find(" ");
		token = line.substr(0, i);
		line.erase(0, i + 1);
		a = std::stod(token);

		// b
		i = line.find(" ");
		token = line.substr(0, i);
		line.erase(0, i + 1);
		b = std::stod(token);

		// c
		i = line.find(" ");
		token = line.substr(0, i);
		line.erase(0, i + 1);
		c = std::stod(token);

		// d
		i = line.find(" ");
		token = line.substr(0, i);
		line.erase(0, i + 1);
		d = std::stod(token);

		// e
		i = line.find(" ");
		token = line.substr(0, i);
		line.erase(0, i + 1);
		e = std::stod(token);

		// f
		i = line.find(" ");
		token = line.substr(0, i);
		line.erase(0, i + 1);
		f = std::stod(token);

		// g
		i = line.find(" ");
		token = line.substr(0, i);
		line.erase(0, i + 1);
		g = std::stod(token);

		if(type == light)
		{
			AddLight(Light(Vector3(a, b, c), Vector3(d, e, f), g));
		}
		else if(type == sphere)
		{
			AddSphere(Sphere(Vector3(a, b, c), d));
		}
		else
		{
			std::cout << "Unknown entity type " << type << std::endl;
		}
	}
	std::cout << "Scene loaded" << std::endl;

}

void FileScene::Draw()
{
	Scene::Draw();
}

void FileScene::Update(double dt)
{
	Scene::Update(dt);
}