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
	int type;
	int i;
	int max;

	while(!file.eof())
	{
		std::getline(file, line);

		if(line.size() == 0)
			break;
		
		// entity type
		i = line.find(" ");
		token = line.substr(0, i);
		line.erase(0, i + 1);
		type = std::stoi(token);

		std::vector<double> params;

		switch(type)
		{
			case 0: // light
				max = 7;
				break;
			case 1: // sphere
				max = 4;
				break;
			case 2: // triangle
				max = 9;
				break;
			case 3: // 2.5D Wall
				max = 4;
				break;
			default:
				max = 0;
				std::cout << "Unknown entity type " << type << std::endl;
				break;
		}

		for(int p = 0; p < max; p++)
		{
			i = line.find(" ");
			token = line.substr(0, i);
			line.erase(0, i + 1);
			params.push_back(std::stod(token));
		}

		switch(type)
		{
			case 0: // light
				AddLight(Light(Point3(params[0], params[1], params[2]), Vector3(params[3], params[4], params[5]), params[6]));
				break;
			case 1: // sphere
				AddSphere(Sphere(Point3(params[0], params[1], params[2]), params[3]));
				break;
			case 2: // triangle
				AddTriangle(Triangle(Point3(params[0], params[1], params[2]), Point3(params[3], params[4], params[5]), Point3(params[6], params[7], params[8])));
				break;
			case 3: // 2.5D Wall
				AddWall(Wall(Point3(params[0], 0, params[1]), Point3(params[2], 0, params[3])));
				break;
			default:
				std::cout << "Unknown entity type " << type << std::endl;
				break;
		}
	}
	std::cout << "Scene loaded" << std::endl;

}

void FileScene::Draw()
{
	Scene::Draw();
	/*for(auto& wall : walls)
	{
		std::tuple<Point3, Point3> pos = wall.GetPosition();
		Point3 a = std::get<0>(pos);
		Point3 b = std::get<1>(pos);
		DebugLine(a, b);
	}*/
}

void FileScene::Update(double dt)
{
	Scene::Update(dt);
}