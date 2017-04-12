#include "scene.hpp"

void Scene::AddSphere(Sphere s)
{
	spheres.push_back(s);
}

void Scene::AddLight(Light l)
{
	lights.push_back(l);
}

TestScene::TestScene()
{
	spheres.push_back(Sphere(Vector3(50, 50, -50), 10));
	lights.push_back(Light(Point3(100, 100, -40)));
}
