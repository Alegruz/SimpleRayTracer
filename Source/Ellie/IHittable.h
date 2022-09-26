#pragma once

#include <cstdint>
#include <iostream>

#include "IMaterial.h"
#include "Ray.h"
#include "Vector3f.h"

namespace ellie
{
    struct HitRecord
    {
        Point3f Point;
        Vector3f Normal;
        IMaterial* Material;
        float Scalar;
        bool bIsFrontFacing;

        inline void SetFaceNormal(const Ray& ray, const Vector3f& outwardNormal) noexcept
        {
            bIsFrontFacing = Dot(ray.Direction, outwardNormal) < 0.0f;
            Normal = (2.0f * static_cast<float>(bIsFrontFacing) - 1.0f) * outwardNormal;
        }

    private:
        uint8_t mPadding[3];
    };

    class IHittable
    {
    public:
        virtual ~IHittable() = default;

        virtual bool HasHit(const Ray& ray, float minScalar, float maxScalar, HitRecord& outRecord) const noexcept = 0;
    };
} // namespace ellie