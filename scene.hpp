#pragma once

#include <vector>
#include <iterator>
#include "geo.hpp"
#include "light.hpp"

class Scene {
public:
	void Draw(void);

	void AddSphere(Sphere h);
	void AddLight(Light l);
private:
	Sphere* FirstHit(Vector3& dir);

protected:
	unsigned width, height;
	Point3 camera;
	double camera_dist;
	std::vector<Sphere> spheres;
	std::vector<Light> lights;
};

class TestScene : public Scene {
public:
	TestScene();
};
