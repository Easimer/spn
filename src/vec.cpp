#include "vec.hpp"
#include <cmath>

Vector3::Vector3() : Vector3(0, 0, 0) {}
Vector3::Vector3(double x) : Vector3(x, 0, 0) {}
Vector3::Vector3(double x, double y) : Vector3(x, y, 0) {}

Vector3::Vector3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const Vector3& v)
{
	this->x = v[0];
	this->y = v[1];
	this->z = v[2];
}

inline double Vector3::GetX(void) { return this->x; }
inline double Vector3::GetY(void) { return this->y; }
inline double Vector3::GetZ(void) { return this->z; }

Vector3 operator+(Vector3 a, Vector3 b)
{
	return Vector3(a.GetX() + b.GetX(), a.GetY() + b.GetY(), a.GetZ() + b.GetZ());
}

Vector3 operator-(Vector3 a, Vector3 b)
{
	return Vector3(a.GetX() - b.GetX(), a.GetY() - b.GetY(), a.GetZ() - b.GetZ());
}

// scalar multiplication
Vector3 operator*(Vector3 a, double b)
{
	return Vector3(a.GetX() * b, a.GetY() * b, a.GetZ() * b);
}

// cross product
Vector3 operator*(Vector3 a, Vector3 b)
{
	return Vector3(a[2]*b[3] - a[3]*b[2], a[3]*b[1]-a[1]*b[3], a[1]*b[2]-a[2]*b[1]);
}

// -- reference --

Vector3 operator+(Vector3& a, Vector3& b)
{
	return Vector3(a.GetX() + b.GetX(), a.GetY() + b.GetY(), a.GetZ() + b.GetZ());
}

Vector3 operator-(Vector3& a, Vector3& b)
{
	return Vector3(a.GetX() - b.GetX(), a.GetY() - b.GetY(), a.GetZ() - b.GetZ());
}

// scalar multiplication
Vector3 operator*(Vector3& a, double b)
{
	return Vector3(a.GetX() * b, a.GetY() * b, a.GetZ() * b);
}

// cross product
Vector3 operator*(Vector3& a, Vector3& b)
{
	return Vector3(a[2]*b[3] - a[3]*b[2], a[3]*b[1]-a[1]*b[3], a[1]*b[2]-a[2]*b[1]);
}

std::ostream& operator<<(std::ostream& os, Vector3& v)
{
	os << "(" << v.GetX() << ", " << v.GetY() << ", " << v.GetZ() << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, Vector3 v)
{
	os << "(" << v.GetX() << ", " << v.GetY() << ", " << v.GetZ() << ")";
	return os;
}

double Vector3::Dot(Vector3 a, Vector3 b)
{
	return a.GetX() * b.GetX() + a.GetY() * b.GetY() + a.GetZ() * b.GetZ();
}

double Vector3::operator[](const int index) const
{
	switch(index)
	{
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
	}
	return 0;
}

bool operator==(Vector3 a, Vector3 b)
{
	return (a[0] - b[0] < VEQ_EPS) && (a[1] - b[1] < VEQ_EPS) && ((a[2] - b[2] < VEQ_EPS));
}

Vector3 operator/(Vector3 a, double b)
{
	return Vector3(a[0] / b, a[1] / b, a[2] / b);
}

Vector3 operator/(Vector3& a, double b)
{
	return Vector3(a[0] / b, a[1] / b, a[2] / b);
}

double Vector3::GetLength(void)
{
	return sqrt(x * x + y * y + z * z);
}

void Vector3::SetX(double x)
{
	this->x = x;
}

void Vector3::SetY(double y)
{
	this->y = y;
}

void Vector3::SetZ(double z)
{
	this->z = z;
}

Vector3 Vector3::Normalize(void)
{
	double l = GetLength();
	return Vector3(x / l, y / l, z / l);
}
