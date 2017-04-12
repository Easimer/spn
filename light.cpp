#include "light.hpp"

Light::Light() : Light(Point3(0, 0, 0), Vector3(255, 255, 255), 20) {}
Light::Light(Point3 position) : Light(position, Vector3(255, 255, 255), 20) {}
Light::Light(Point3 position, Vector3 color) : Light(position, color, 20) {}
Light::Light(Point3 position, Vector3 color, double brightness) 
{
	this->position = Point3(position);
	this->color = Vector3(color);
	this->brightness = brightness;
}

Vector3 Light::GetColor(void)
{
	return Vector3(color);
}

double Light::GetBrightness(void)
{
	return brightness;
}

Vector3 Light::GetPosition(void)
{
	return Vector3(position);
}
