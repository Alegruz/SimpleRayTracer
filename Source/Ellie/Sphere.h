#include <cmath>
#include <iostream>

#include "IHittable.h"
#include "IMaterial.h"
#include "Ray.h"
#include "Shape.h"
#include "Vector3f.h"

namespace ellie
{
    class Sphere final : public IIntersectable, public IHittable
    {
    public:
        explicit constexpr Sphere() noexcept = delete;
        explicit Sphere(const Point3f& center, float radius, IMaterial* material) noexcept;
        explicit constexpr Sphere(const Sphere& other) noexcept = default;
        explicit constexpr Sphere(Sphere&& other) noexcept = default;
        constexpr Sphere& operator=(const Sphere& other) noexcept = default;
        constexpr Sphere& operator=(Sphere&& other) noexcept = default;
        constexpr ~Sphere() noexcept = default;

        constexpr bool HasIntersected(const Ray& ray) noexcept override;
        float GetClosestIntersection(const Ray& ray) noexcept override;
        bool HasHit(const Ray& ray, float minScalar, float maxScalar, HitRecord& outRecord) const noexcept override;

    public:
        Point3f Center;
        float Radius;

    private:
        float mPadding = 0.0f;

    public:
        IMaterial* Material;
    };

    constexpr bool Sphere::HasIntersected(const Ray& ray) noexcept
    {
        Vector3f centerToOrigin = ray.Origin - Center;
        float a = ray.Direction.GetLengthSquared();
        float halfB = Dot(centerToOrigin, ray.Direction);
        float c = centerToOrigin.GetLengthSquared() - Radius * Radius;
        float discriminant = halfB * halfB - a * c;

        return discriminant > 0.0f;
    }
} // namespace ellie