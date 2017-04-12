#pragma once

#include <vector>
#include <iterator>
#include "geo.hpp"
#include "light.hpp"

class Scene {
public:
	void AddSphere(Sphere h);
	void AddLight(Light l);
protected:
	Point3 camera;
	std::vector<Sphere> spheres;
	std::vector<Light> lights;
};

class TestScene : public Scene {
public:
	TestScene();
};
