#include "Lambertian.h"

namespace ellie
{
    bool Lambertian::Scatter(const Ray& ray, const HitRecord& hitRecord, Color& outAttenuation, Ray& outScattered) const noexcept
    {
        (void) (ray);
        Vector3f scatterDirection = hitRecord.Normal + Math::GetRandomUnitVector3f();

        if (scatterDirection.IsNearZero())
        {
            scatterDirection = hitRecord.Normal;
        }

        outScattered = Ray(hitRecord.Point, scatterDirection);
        outAttenuation = Albedo;
        return true;
    }
} // namespace ellie