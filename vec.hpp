#pragma once

#include <iostream>

#define VEQ_EPS (0.001)

class Vector3 {
public:
	Vector3();
	Vector3(double x);
	Vector3(double x, double y);
	Vector3(double x, double y, double z);
	Vector3(const Vector3& v);
	double operator[](const int index) const;
	double GetLength(void);
	inline double GetX(void);
	inline double GetY(void);
	inline double GetZ(void);
	static double Dot(Vector3& a, Vector3& b);
private:
	double x, y, z;
};

typedef Vector3 Point3;

Vector3 operator+(Vector3& a, Vector3& b);
Vector3 operator-(Vector3& a, Vector3& b);
Vector3 operator*(Vector3& a, Vector3& b);
bool operator==(Vector3 a, Vector3 b);
Vector3 operator*(Vector3& a, double b);
Vector3 operator/(Vector3& a, double b);
std::ostream& operator<<(std::ostream& os, Vector3& v);
std::ostream& operator<<(std::ostream& os, Vector3 v);
