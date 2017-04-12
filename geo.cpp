#include "geo.hpp"

Sphere::Sphere() : Sphere(0, 0, 0, 10) {}
Sphere::Sphere(double x, double y, double z) : Sphere(Vector3(x, y, z), 10) {}
Sphere::Sphere(double x, double y, double z, double radius) : Sphere(Vector3(x, y, z), radius)  {}
Sphere::Sphere(const Point3& position) : Sphere(position, 10) {}
Sphere::Sphere(const Point3& position, double radius)
{
	this->position = Point3(position);
	this->radius = radius;
}
