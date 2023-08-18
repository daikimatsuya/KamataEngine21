#pragma once
#include "AABB.h"
#include "Sphere.h"
#include "VectorFanctions.h"
class AABBToSphereCollision
{
public:
	bool IsCollision(const AABB& aabb, const Sphere& sphere);
private:
	VectorFanctions vf_;
};

