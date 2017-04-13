#include "scene.hpp"
#include <limits>
#include <cmath>
#include "geo.hpp"
#include "vec.hpp"

void Scene::AddSphere(Sphere s)
{
	spheres.push_back(s);
}

void Scene::AddLight(Light l)
{
	lights.push_back(l);
}

FirstHitResult Scene::FirstHit(Vector3& src, Vector3& dir)
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
		Vector3 cg = src - sphere.GetPosition();
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
		double D = (src - l_hit).GetLength();
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
	//std::cout << "Scene::Draw" << std::endl;
	Point3 screen_topleft(camera[0] - width / 2, camera[1] - height / 2, camera[2] - camera_dist);
	Point3 px(screen_topleft);
	for(unsigned x = 0; x < width; x++)
	{
		px.SetX(screen_topleft[0] + x);

		for(unsigned y = 0; y < height; y++)
		{
			px.SetY(screen_topleft[1] + y);
			Vector3 cpx = (camera - px).Normalize();
			FirstHitResult res = FirstHit(camera, cpx);
			if(!res.result)
			{
				continue;
			}

			double u, v;
			Vector3 d = (res.hit - res.result->GetPosition()).Normalize();
			u = 0.5 + (atan2(d[2], d[0]) / (2 * M_PI));
			v = 0.5 - asin(d[1]) / M_PI;

			double r = 0, g = 0, b = 0;
			double s = 0; // TEMP
			int n = 0;
			for(auto& light_src : lights)
			{
				Point3 light = light_src.GetPosition();
				Vector3 lcolor = light_src.GetColor();
				double bright = light_src.GetBrightness();

				Vector3 pl = light - res.hit;
				Vector3 pln = pl.Normalize();
				//if(FirstHit(light, pln).result != res.result)
					//continue;

				double d = pl.GetLength();
				double a = Vector3::Dot(res.normal, pl) / (res.normal.GetLength() * pl.GetLength());
				if(a <= 0)
					continue;
				a = a / (d/bright);
				if(a > 1.0)
					a = 1.0;
				r += a * (lcolor[0]);
				g += a * (lcolor[1]);
				b += a * (lcolor[2]);
				s += a; // TEMP
				//std::cout << "\nA: " << a << std::endl;
				//std::cout << "L: (" << a * lcolor[0] << ',' << a * lcolor[1] << ',' << a * lcolor[2] << ')' << std::endl;
				n++;
			}
			if(n > 0)
			{
				// TEMP

				// calculate light color

				Vector3 lc(r / n, g / n, b / n);

				// calculate texture color
				double radius = res.result->GetRadius() * 2;
				int ux = (int)(radius * u);
				int vy = (int)(radius * v);
				if(
					(((ux & 1) == 0) && ((vy & 1) == 0)) ||
					(((ux & 1) == 1) && ((vy & 1) == 1))
				)
				{
					renderer->SetColor(((s + lc[0]) / 2) * 255, lc[1] * 255, lc[2] * 255);
				}
				else
				{
					Vector3 white(1 * s, 1 * s, 1 * s);
					Vector3 rgb((s + lc[0]) / 2, (s + lc[1]) / 2, (s + lc[2]) / 2);
					renderer->SetColor(rgb[0] * 255, rgb[1] * 255, rgb[2] * 255);
				}
				// TEMP
				renderer->PlotPixel(x, y);
			}
		}
	}
}

TestScene::TestScene(Renderer& r)
{
	this->renderer = &r;
	width = r.GetWidth(); height = r.GetHeight();
	camera = Point3(0, 0, 0);
	camera_dist = (width / 2) * tan(45 * (M_PI / 180));
	spheres.push_back(Sphere(Vector3(-30, 0, 150), 30));
	spheres.push_back(Sphere(Vector3(-16, 0, 100), 15));
	lights.push_back(Light(Point3(0, 0, 0), Vector3(0.0, 0.0, 1.0), 75));
}

void TestScene::Draw()
{
	Scene::Draw();
}

void TestScene::Update(double dt)
{
	
}
