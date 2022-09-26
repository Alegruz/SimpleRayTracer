#include "Metal.h"

namespace ellie
{
    bool Metal::Scatter(const Ray& ray, const HitRecord& hitRecord, Color& outAttenuation, Ray& outScattered) const noexcept
    {
        Vector3f reflect = Reflect(GetUnitVector(ray.Direction), hitRecord.Normal);

        outScattered = Ray(hitRecord.Point, reflect + Fuzz * Math::GetRandomUnitSphereVector3f());
        outAttenuation = Albedo;
        return Dot(outScattered.Direction, hitRecord.Normal) > 0.0f;
    }
} // namespace ellie