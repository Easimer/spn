#pragma once

#include <vector>
#include <iterator>
#include "geo.hpp"
#include "light.hpp"
#include "renderer.hpp"

class FirstHitResult {
public:
	Sphere* result;
	Point3 hit;
	Vector3 normal;
};

class Scene {
public:
	Scene(Renderer& r);
	void Update(double dt);
	void Draw(void);

	void AddSphere(Sphere h);
	void AddLight(Light l);
private:
	FirstHitResult FirstHit(Vector3& src, Vector3& dir);

protected:
	unsigned width, height;
	Point3 camera;
	double camera_dist;
	std::vector<Sphere> spheres;
	std::vector<Light> lights;
	Renderer* renderer;
	double et;
};

class TestScene : public Scene {
public:
	TestScene(Renderer& r);
	void Update(double dt);
	void Draw(void);
};
