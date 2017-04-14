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

Point3 Sphere::GetPosition(void)
{
	return Point3(this->position);
}

double Sphere::GetRadius(void)
{
	return this->radius;
}

Triangle::Triangle() : Triangle(ORIGIN, ORIGIN, ORIGIN) {}
Triangle::Triangle(const Point3& p1, const Point3& p2, const Point3& p3)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}

bool Triangle::Contains(const Point3& p)
{
	Vector3 v0 = p3 - p1;
	Vector3 v1 = p2 - p1;
	Vector3 v2 = p - p1;

	double dot00 = Vector3::Dot(v0, v0);
	double dot01 = Vector3::Dot(v0, v1);
	double dot02 = Vector3::Dot(v0, v2);
	double dot11 = Vector3::Dot(v1, v1);
	double dot12 = Vector3::Dot(v1, v2);

	double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	return (u >= 0) && (v >= 0) && (u + v < 1);
}

Vector3 Triangle::GetNormal(void)
{
	return (p1 - p2) * (p3 - p2);
}

std::tuple<Point3, Point3, Point3> Triangle::GetPosition(void)
{
	return {p1, p2, p3};
}

Wall::Wall(const Point3& p1, const Point3& p2)
{
	this->p1 = p1;
	this->p2 = p2;
}

std::tuple<Point3, Point3> Wall::GetPosition(void)
{
	return {p1, p2};
}

Vector3 Wall::GetNormal(void)
{
	Vector3 v = (p1 - p2);
	return Vector3(v[0], v[1], -v[2]);
}
