#include "Dielectric.h"

namespace ellie
{
    bool Dielectric::Scatter(const Ray& ray, const HitRecord& hitRecord, Color& outAttenuation, Ray& outScattered) const noexcept
    {
        outAttenuation = Color(1.0f, 1.0f, 1.0f);
        float refractionRatio = hitRecord.bIsFrontFacing ? (1.0f / IndexOfRefraction) : IndexOfRefraction;

        Vector3f unitDirection = GetUnitVector(ray.Direction);

        float cosTheta = fmin(Dot(-unitDirection, hitRecord.Normal), 1.0f);
        float sinTheta = sqrt(1.0f - cosTheta * cosTheta);

        bool bCannotRefract = refractionRatio * sinTheta > 1.0f;
        Vector3f direction;

        if (bCannotRefract || reflectance(cosTheta, refractionRatio) > Math::GetRandom())
        {
            direction = Reflect(unitDirection, hitRecord.Normal);
        }
        else
        {
            direction = Refract(unitDirection, hitRecord.Normal, refractionRatio);
        }

        outScattered = Ray(hitRecord.Point, direction);
        
        //Vector3f refracted = Refract(unitDirection, hitRecord.Normal, refractionRatio);
        //outScattered = Ray(hitRecord.Point, refracted);
        return true;
    }

    float Dielectric::reflectance(float cosine, float refIdx)
    {
        // Use Schlick's approximation for reflectance.
        float r0 = (1.0f - refIdx) / (1.0f + refIdx);
        r0 = r0 * r0;
        return r0 + (1.0f - r0) * pow((1.0f - cosine), 5.0f);
    }
} // namespace ellie