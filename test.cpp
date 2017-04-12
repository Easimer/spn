#include <iostream>
#include <cassert>

#define V1_X	2
#define V1_Y	1
#define V1_Z	-6

#define V2_X	-10
#define V2_Y	5
#define V2_Z	10

#define SC 2.5

#include "vec.hpp"
#include "geo.hpp"

int main(int argc, char** argv)
{
	Vector3 v1(V1_X, V1_Y, V1_Z);
	Vector3 v2(V2_X, V2_Y, V2_Z);
	// add
	assert((v1 + v2) == Vector3(V1_X + V2_X, V1_Y + V2_Y, V1_Z + V2_Z));
	// subtract
	assert((v1 - v2) == Vector3(V1_X - V2_X, V1_Y - V2_Y, V1_Z - V2_Z));
	// vec multiple
	//assert((v1 * v2) == Vector3(V1_X * V2_X, V1_Y * V2_Y, V1_Z * V2_Z));
	// vec scalar multiple
	assert((v1 * SC) == Vector3(V1_X * SC, V1_Y * SC, V1_Z * SC));
	// vec scalar multiple
	assert((v1 / SC) == Vector3(V1_X / SC, V1_Y / SC, V1_Z / SC));

	std::cout << "Tests has succeded" << std::endl;
	return 0;
}
