#pragma once

#include <vector>
#include <iterator>
#include <stdint.h>
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
	RC_NONE,
	RC_SPHERE,
	RC_TRIANGLE,
	RC_WALL,
	RC_GROUND
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
	~Scene();
	void Update(double dt);
	void Draw(void);

	void AddSphere(Sphere h);
	void AddLight(Light l);
	void AddTriangle(Triangle t);
	void AddWall(Wall w);
	Light* GetLight(unsigned i);
	Sphere* GetSphere(unsigned i);

	Point3 WorldToScreen(const Point3& w);
	Point3 ScreenToWorld(const Point3& s);

	void DebugLine(const Point3& a, const Point3& b);
	void DebugDot(const Point3& a);

	const char* ScriptName(void);

	std::tuple<RaycastHit, Vector3, int> Reflect(const Point3& src, const Vector3& dir, int level);
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
	std::string scriptname;
};

struct cbuf {
	uint8_t r, g, b;
};

class TestScene : public Scene {
public:
	TestScene(Renderer& r);
	void Update(double dt);
	void Draw(void);
};
