#pragma once
#include "AABB.h"
#include "Matrix4x4.h"
#include "stdint.h"
#include "VectorFanctions.h"
#include "AffineMatrixFunctions.h"
class AABBToAABBCollision
{
public:
	bool IsCollision(const AABB& aabb1, const AABB& aabb2);
	void Draw(const AABB& aabb, const Matrix4x4& viewprojectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
private:
	VectorFanctions vf_;
	AffineMatrixFunctions amf_;
};

