#pragma once

#include "vec.hpp"

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

