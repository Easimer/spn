#pragma once

#include <tuple>
#include "vec.hpp"

#define ORIGIN Point3(0, 0, 0)

class Sphere {
public:
	Sphere();
	Sphere(const Point3& pos);
	Sphere(const Point3& pos, double radius);
	Sphere(double x, double y, double z);
	Sphere(double x, double y, double z, double radius);
	Point3 GetPosition(void);
	double GetRadius(void);
private:
	Point3 position;
	double radius;
};

class Plane {
public:
	Plane();
	Plane(const Point3& p1, const Point3& p2);
	std::tuple<Point3, Point3> GetPosition(void);
private:
	Point3 p1, p2;
};

class Triangle {
public:
	Triangle();
	Triangle(const Point3& p1, const Point3& p2, const Point3& p3);
	std::tuple<Point3, Point3, Point3> GetPosition(void);
	bool Contains(const Point3& p);
	Vector3 GetNormal(void);
private:
	Point3 p1, p2, p3;
};

class Wall {
public:
	Wall(const Point3& p1, const Point3& p2);
	std::tuple<Point3, Point3> GetPosition(void);
	Vector3 GetNormal(void);
private:
	Point3 p1, p2;
};
