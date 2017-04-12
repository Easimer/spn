#pragma once

#include "vec.hpp"

class Light : public Point3 {
public:
	Light();
	Light(Vector3 color);
	Light(Vector3 color, double brightness);
	Vector3 GetColor(void);
	double GetBrightness(void);
private:
	Vector3 color;
	double brightness;
};
