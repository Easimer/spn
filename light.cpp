#include "light.hpp"

Light::Light() : Light(Vector3(255, 255, 255), 100) {}
Light::Light(Vector3 color) : Light(color, 100) {}
Light::Light(Vector3 color, double brightness) 
{
	this->color = Vector3(color);
	this->brightness = brightness;
}

Vector3 Light::GetColor(void)
{
	return Vector3(this->color);
}

double Light::GetBrightness(void)
{
	return this->brightness;
}
