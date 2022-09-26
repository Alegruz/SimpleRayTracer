#pragma once

#include <cmath>

#include "Color.h"
#include "IHittable.h"
#include "IMaterial.h"
#include "Math.h"
#include "Ray.h"
#include "Vector3f.h"

namespace ellie
{
    class Dielectric : public IMaterial
    {
    public:
        explicit constexpr Dielectric() noexcept = delete;
        explicit constexpr Dielectric(float indexOfRefraction) noexcept;
        explicit constexpr Dielectric(const Dielectric& other) noexcept = default;
        explicit constexpr Dielectric(Dielectric&& other) noexcept = default;
        constexpr Dielectric& operator=(const Dielectric& other) noexcept = default;
        constexpr Dielectric& operator=(Dielectric&& other) noexcept = default;
        virtual ~Dielectric() noexcept = default;

        virtual bool Scatter(const Ray& ray, const HitRecord& hitRecord, Color& outAttenuation, Ray& outScattered) const noexcept override;

    public:
        float IndexOfRefraction;

    private:
        static float reflectance(float cosine, float refIdx);

    private:
        uint32_t mPadding;
    };

    constexpr Dielectric::Dielectric(float indexOfRefraction) noexcept
        : IndexOfRefraction(indexOfRefraction)
    {
    }
} // namespace ellie