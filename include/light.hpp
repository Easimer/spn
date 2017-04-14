#pragma once

#include "vec.hpp"

class Light {
public:
	Light();
	Light(Point3 position);
	Light(Point3 position, Vector3 color);
	Light(Point3 position, Vector3 color, double brightness);
	Vector3 GetPosition(void);
	Vector3* GetPositionUnsafe(void);
	Vector3* GetColorUnsafe(void);
	Vector3 GetColor(void);
	double GetBrightness(void);
	void SetBrightness(double b);
private:
	Point3 position;
	Vector3 color;
	double brightness;
};
