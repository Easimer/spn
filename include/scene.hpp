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

typedef enum {
	RC_SPHERE,
	RC_TRIANGLE,
	RC_WALL
} RaycastHitType;

class RaycastHit {
public:
	void* object;
	RaycastHitType type;
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
	void AddTriangle(Triangle t);
	void AddWall(Wall w);

	Point3 WorldToScreen(const Point3& w);
	Point3 ScreenToWorld(const Point3& s);

	void DebugLine(const Point3& a, const Point3& b);
	void DebugDot(const Point3& a);
private:
	FirstHitResult FirstHit(Vector3& src, Vector3& dir);
	RaycastHit Raycast(Vector3& src, Vector3& dir);

protected:
	unsigned width, height;
	Point3 camera;
	double camera_dist;
	std::vector<Sphere> spheres;
	std::vector<Light> lights;
	std::vector<Triangle> triangles;
	std::vector<Wall> walls;
	Renderer* renderer;
	double et;
};

class TestScene : public Scene {
public:
	TestScene(Renderer& r);
	void Update(double dt);
	void Draw(void);
};
