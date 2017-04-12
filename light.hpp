#pragma once

#include "vec.hpp"

class Light : public Point3 {
public:
	Light();
	Light(Point3 position);
	Light(Point3 position, Vector3 color);
	Light(Point3 position, Vector3 color, double brightness);
	Vector3 GetColor(void);
	double GetBrightness(void);
private:
	Point3 position;
	Vector3 color;
	double brightness;
};
