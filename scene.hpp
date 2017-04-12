#pragma once

#include <vector>
#include <iterator>
#include "geo.hpp"
#include "light.hpp"

class Scene {
public:
	void AddSphere(Sphere h);
	void AddLight(Light l);

	auto s_begin() { return spheres.begin(); }
	auto l_begin() { return lights.begin(); }
private:
	std::vector<Sphere> spheres;
	std::vector<Light> lights;
};
