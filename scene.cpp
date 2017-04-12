#include "scene.hpp"
#include "geo.hpp"
#include "vec.hpp"
#include <limits>
#include <cmath>

void Scene::AddSphere(Sphere s)
{
	spheres.push_back(s);
}

void Scene::AddLight(Light l)
{
	lights.push_back(l);
}

FirstHitResult Scene::FirstHit(Vector3& dir)
{
	// dir = NORMALIZE(C - W(P))
	FirstHitResult res;

	Sphere* min = NULL;
	auto min_dist = std::numeric_limits<double>::infinity();
	Point3 hit;
	Vector3 normal;
	for(auto& sphere : spheres)
	{
		Vector3 gp = sphere.GetPosition();
		double gr = sphere.GetRadius();
		double grsq = gr * gr;
		Vector3 cg = camera - sphere.GetPosition();
		double d = Vector3::Dot(cg, dir);
		if(d > 0 || Vector3::Dot(cg, cg) < grsq)
		{
			continue;
		}

		Vector3 a = cg - dir * d;
		double asq = Vector3::Dot(a, a);
		if(asq > grsq)
		{
			continue;
		}
		double h = sqrt(grsq - asq);
		Vector3 i = a - dir * h;
		Point3 l_hit = gp + i;
		double D = (camera - l_hit).GetLength();
		if(D < min_dist)
		{
			min_dist = D;
			min = &sphere;
			hit = l_hit;
			normal = i / gr;
		}
	}
	res.result = min;
	res.hit = Vector3(hit);
	res.normal = Vector3(normal);
	return res;
}

void Scene::Draw(void)
{
	Point3 screen_topleft(camera[0] - width / 2, camera[1] - height / 2, camera[2] + camera_dist);
	Point3 px(screen_topleft);

	for(unsigned x = 0; x < width; x++)
	{
		px.SetX(screen_topleft[0] + x);
		for(unsigned y = 0; y < height; y++)
		{
			px.SetY(screen_topleft[1] + y);
			Vector3 cpx = (camera - px).Normalize();
			FirstHitResult res = FirstHit(cpx);
			if(!res.result)
				continue;
			
		}
	}
}

TestScene::TestScene(Renderer& r)
{
	this->renderer = &r;
	width = r.GetWidth(); height = r.GetHeight();
	camera = Point3(0, 0, 0);
	camera_dist = 50;
	spheres.push_back(Sphere(Vector3(50, 50, -50), 10));
	lights.push_back(Light(Point3(100, 100, -40)));
}
