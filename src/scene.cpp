#include "scene.hpp"
#include <iostream>
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

void Scene::AddTriangle(Triangle t)
{
	triangles.push_back(t);
}

void Scene::AddWall(Wall w)
{
	walls.push_back(w);
}

/*RaycastHit Scene::Raycast2(Point3& p_0, Vector3& v)
{
	// Raycast
	// p_0 is the source of the ray
	// v is a normalized vector; the direction of the ray
	// -----
	// res contains which object was hit, where was it hit and the normal vec

	RaycastHit res;
	res.object = NULL;

	double min = std::numeric_limits<double>::infinity();

	for(auto& triangle : triangles)
	{
		Vector3 n = triangle.GetNormal();
		double denom = Vector3::Dot(n, v);
		if(fabs(denom) > VEQ_EPS)
		{
			double t = Vector3::Dot((std::get<0>(triangle.GetPosition()) - p_0), n) / denom;
			if(t >= 0)
			{
				Point3 I = p_0 + t * v;
				if(triangle.Contains(I))
				{
					if(t < min)
					{
						min = t;
						res.object = &triangle;
						res.type = RC_TRIANGLE;
						res.hit = I;
						res.normal = n;
					}
				}
			}
		}
	}

	return res;
}*/

RaycastHit Scene::Raycast(Point3& src, Vector3& dir)
{
	// dir = NORMALIZE(C - W(P))
	RaycastHit res;

	res.object = NULL;
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
			res.object = &sphere;
			res.type = RC_SPHERE;
			res.hit = l_hit;
			res.normal = i / gr;
		}
	}
	for(auto& wall : walls)
	{
		Vector3 dir2(dir[0], 0, dir[2]);

		auto pos = wall.GetPosition();
		Point3 W1 = std::get<0>(pos);
		Point3 W2 = std::get<1>(pos);

		double p0_x = W1[0], p0_y = W1[2];
		double p1_x = W2[0], p1_y = W2[2];
		double p2_x = dir2[0], p2_y = dir2[2];
		double p3_x = dir2[0] * 1000, p3_y = dir2[2] * 1000;

		double s1_x, s1_y, s2_x, s2_y;
		s1_x = p1_x - p0_x; s1_y = p1_y - p0_y;
    	s2_x = p3_x - p2_x; s2_y = p3_y - p2_y;

    	double s, t, D;
    	D = -s2_x * s1_y + s1_x * s2_y;
    	if(fabs(D) < 0.001)
    	{
    		continue;
    	}

    	s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / D;
    	t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / D;

    	if(s >= 0 && s <= 1 && t >= 0 && t <= 1)
    	{
    		Vector3 I(p0_x + (t*s1_x));
    		double d = (src - I).GetLength();
    		if(d < min_dist)
    		{
    			min_dist = d;
    			res.object = &wall;
    			res.type = RC_WALL;
    			res.hit = I;
    			res.normal = wall.GetNormal();
    		}
    	}
	}
	return res;
}

void Scene::Draw(void)
{
	std::cout << "Scene::Draw" << std::endl;
	Point3 screen_topleft(camera[0] - width / 2, camera[1] - height / 2, camera[2] - camera_dist);
	Point3 px(screen_topleft);
	for(unsigned x = 0; x < width; x++)
	{
		px.SetX(screen_topleft[0] + x);

		for(unsigned y = 0; y < height; y++)
		{
			px.SetY(screen_topleft[1] + y);
			Vector3 cpx = (camera - px).Normalize();
			RaycastHit res = Raycast(camera, cpx);
			if(!res.object)
			{
				continue;
			}

			if(res.type == RC_TRIANGLE)
			{
				Triangle* t = (Triangle*)res.object;
				std::cout << res.hit << std::endl;

				double r = 0, g = 0, b = 0;
				int n = 1;

				for(auto& light_src : lights)
				{
					Point3 l_p = light_src.GetPosition();
					Vector3 l_c = light_src.GetColor();
					double l_b = light_src.GetBrightness();

					Vector3 lp = (l_p - res.hit);
					double dist_sq = Vector3::Dot(lp, lp);
					double a = Vector3::Dot(res.normal, lp) / (res.normal.GetLength() * lp.GetLength());
					if(a <= 0)
						continue;
					a = (a * l_b) / dist_sq;
					if(a > 1.0)
						a = 1.0;
					r += a * l_c[0];
					g += a * l_c[1];
					b += a * l_c[2];
					n++;
				}

				renderer->SetColor(r/n, g/n, b/n);
				renderer->PlotPixel(x, y);
			}
			else if(res.type == RC_SPHERE)
			{
				renderer->SetColor(0, 0, 0);
				renderer->PlotPixel(x, y);
				double u, v;
				Vector3 d = (res.hit - ((Sphere*)res.object)->GetPosition()).Normalize();
				u = 0.5 + (atan2(d[2], d[0]) / (2 * M_PI));
				v = 0.5 - asin(d[1]) / M_PI;

				double r = 0, g = 0, b = 0;
				double s = 0; // TEMP
				int n = 1;
				for(auto& light_src : lights)
				{
					Point3 light = light_src.GetPosition();
					Vector3 lcolor = light_src.GetColor();
					double bright = light_src.GetBrightness();

					Vector3 pl = light - res.hit;

					double d = pl.GetLength();
					double a = Vector3::Dot(res.normal, pl) / (res.normal.GetLength() * pl.GetLength());
					if(a <= 0)
						continue;
					a = ((a * bright) / (d * d * 4 * M_PI));
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
					double radius = ((Sphere*)res.object)->GetRadius();
					int ux = (int)(radius * u);
					int vy = (int)(radius * v);
					if(
						(ux & 1) == (vy & 1)
					)
					{
						renderer->SetColor(((s + lc[0]) / n) * 255, lc[1] * 255, lc[2] * 255);
					}
					else
					{
						Vector3 rgb((s + lc[0]) / n, (s + lc[1]) / n, (s + lc[2]) / n);
						renderer->SetColor(rgb[0] * 255, rgb[1] * 255, rgb[2] * 255);
					}
					// TEMP
				}
				else
				{
					renderer->SetColor(0, 0, 0);
				}
				renderer->PlotPixel(x, y);
			}
			else if(res.type == RC_WALL)
			{
				Vector3 v(res.hit[0], 0, res.hit[1]);
				Vector3 d = res.hit - camera;

				double max = 64 / d.GetLength();
				if(abs(y - height / 2) > max)
					continue;
				
				renderer->SetColor(255, 0, 0);
				renderer->PlotPixel(x, y);
			}
		}
	}
}

void Scene::Update(double dt)
{
	et += dt;
}

Scene::Scene(Renderer& r)
{
	this->renderer = &r;
	width = r.GetWidth(); height = r.GetHeight();
	camera = Point3(0, 0, 0);
	camera_dist = (width / 2) * tan(45 * (M_PI / 180));
	et = 0.0;
	std::cout << "Scene(" << width << ',' << height << ')' << std::endl;
}

Point3 Scene::WorldToScreen(const Point3& w)
{
	return Point3(w[0] - camera[0] + width / 2, w[1], w[2] - camera[2] + height / 2);
}

Point3 Scene::ScreenToWorld(const Point3& s)
{
	return Point3(camera[0] - width / 2 - s[0], 0, camera[2] - height / 2 - s[2]);
}

void Scene::DebugLine(const Point3& a, const Point3& b)
{
	double dX = a[0] - b[0];
	double dY = a[2] - b[2];

	renderer->SetColor(255, 255, 0);

	if(fabs(dX) < 0.0001)
	{
		Point3 s, e;
		if(a[2] < b[2])
		{
			s = a;
			e = b;
		}
		else
		{
			s = b;
			e = a;
		}
		while(s[2] < e[2])
		{
			Point3 scr = WorldToScreen(s);
			renderer->PlotPixel(scr[0], scr[2]);
			s.SetZ(s[2] + 1);
		}
		return;
	}

	double dE = fabs(dY / dX);
	double E = dE - 0.5;
	int y = a[2];
	int x0 = (a[0] < b[0]) ? a[0] : b[0];
	int x1 = (a[0] < b[0]) ? b[0] : a[0];
	for(int x = x0; x < x1; x++)
	{
		Point3 scr = WorldToScreen(Point3(x, 0, y));
		renderer->PlotPixel(scr[0], scr[2]);
		E += dE;
		if(E >= 0.5)
		{
			y++;
			E -= 1.0;
		}
	}
}

void Scene::DebugDot(const Point3& a)
{
	Point3 w = WorldToScreen(a);
	renderer->SetColor(255, 255, 0);
	renderer->PlotPixel(w[0], w[2]);
}

// TestScene

TestScene::TestScene(Renderer& r) : Scene::Scene(r)
{
	spheres.push_back(Sphere(Vector3(0, 0, 150), 30));
	//lights.push_back(Light(Point3(0, 0, 150), Vector3(0.0, 0.0, 1.0), 75));
	lights.push_back(Light(Point3(50, 0, 100), Vector3(1.0, 0.0, 0.0), 25));
	lights.push_back(Light(Point3(0, 50, 100), Vector3(1.0, 1.0, 1.0), 25));
}

void TestScene::Draw()
{
	Scene::Draw();
}

void TestScene::Update(double dt)
{
	Scene::Update(dt);
	/*Sphere s = spheres.front();
	Point3 sp = s.GetPosition();
	double z = 150 + 5 * sin(et);
	double x = 5 * cos(et);
	sp.SetZ(z);
	sp.SetX(x);
	std::cout << "Z: " << z << " X: " << x << std::endl;*/
}
