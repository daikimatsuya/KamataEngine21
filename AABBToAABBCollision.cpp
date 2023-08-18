#include "AABBToAABBCollision.h"
#include "Novice.h"

bool AABBToAABBCollision::IsCollision(const AABB& a, const AABB& b)
{
    if ((a.min.x <= b.Max.x && a.Max.x >= b.min.x) && (a.min.y <= b.Max.y && a.Max.y >= b.min.y) && (a.min.z <= b.Max.z && a.Max.z >= b.min.z)) {
        return true;
    }
    return false;
}

void AABBToAABBCollision::Draw(const AABB& aabb, const Matrix4x4& viewprojectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
    Vector3 start, end;
    Vector3 length = vf_.Subtract(aabb.Max , aabb.min);

    {
        start = aabb.min;
        end = aabb.min;
        end.x += length.x;

        amf_.ViewTransform(start, viewprojectionMatrix, viewportMatrix);
        amf_.ViewTransform(end, viewprojectionMatrix, viewportMatrix);
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);

        end = aabb.min;
        end.y += length.y;

        amf_.ViewTransform(end, viewprojectionMatrix, viewportMatrix);
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);

        end = aabb.min;
        end.z += length.z;

        amf_.ViewTransform(end, viewprojectionMatrix, viewportMatrix);
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);



    }
    {
        start = aabb.Max;
        end = aabb.Max;
        end.x -= length.x;

        amf_.ViewTransform(start, viewprojectionMatrix, viewportMatrix);
        amf_.ViewTransform(end, viewprojectionMatrix, viewportMatrix);
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);

        end = aabb.Max;
        end.y -= length.y;

        amf_.ViewTransform(end, viewprojectionMatrix, viewportMatrix);
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);

        end = aabb.Max;
        end.z -= length.z;

        amf_.ViewTransform(end, viewprojectionMatrix, viewportMatrix);
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);




    }

    {
        start = aabb.Max;
        start.x -= length.x;
        end = aabb.min;
        end.z += length.z;

        amf_.ViewTransform(start, viewprojectionMatrix, viewportMatrix);
        amf_.ViewTransform(end, viewprojectionMatrix, viewportMatrix);
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);

        end = aabb.min;
        end.y += length.y;

        amf_.ViewTransform(end, viewprojectionMatrix, viewportMatrix);
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);


    }

    {
        start = aabb.Max;
        start.z -= length.z;
        end = aabb.min;
        end.y += length.y;

        amf_.ViewTransform(start, viewprojectionMatrix, viewportMatrix);
        amf_.ViewTransform(end, viewprojectionMatrix, viewportMatrix);
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);

        end = aabb.min;
        end.x += length.x;

        amf_.ViewTransform(end, viewprojectionMatrix, viewportMatrix);
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);

    }

    {
        start = aabb.Max;
        start.z -= length.z;
        end = aabb.min;
        end.y += length.y;

        amf_.ViewTransform(start, viewprojectionMatrix, viewportMatrix);
        amf_.ViewTransform(end, viewprojectionMatrix, viewportMatrix);
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);

        end = aabb.min;
        end.x += length.x;

        amf_.ViewTransform(end, viewprojectionMatrix, viewportMatrix);
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);

    }
}
