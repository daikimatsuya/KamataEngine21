#include "AABBToSphereCollision.h"
#include "algorithm"

bool AABBToSphereCollision::IsCollision(const AABB& aabb, const Sphere& sphere)
{
    Vector3 nearPos{ sphere.center };
    nearPos.x = (std::clamp)(nearPos.x, aabb.min.x, aabb.Max.x);
    nearPos.y = (std::clamp)(nearPos.y, aabb.min.y, aabb.Max.y);
    nearPos.z = (std::clamp)(nearPos.z, aabb.min.z, aabb.Max.z);
    float distance = vf_.Length(vf_.Subtract(nearPos, sphere.center));

    if (distance <= sphere.radius) {
        return true;
    }

    return false;
}