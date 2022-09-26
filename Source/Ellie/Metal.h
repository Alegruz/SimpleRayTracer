#pragma once

#include <algorithm>

#include "Color.h"
#include "IHittable.h"
#include "IMaterial.h"
#include "Math.h"
#include "Ray.h"
#include "Vector3f.h"

namespace ellie
{
    class Metal : public IMaterial
    {
    public:
        explicit constexpr Metal() noexcept = delete;
        explicit constexpr Metal(const Color& albedo, float fuzz) noexcept;
        explicit constexpr Metal(const Metal& other) noexcept = default;
        explicit constexpr Metal(Metal&& other) noexcept = default;
        constexpr Metal& operator=(const Metal& other) noexcept = default;
        constexpr Metal& operator=(Metal&& other) noexcept = default;
        virtual ~Metal() noexcept = default;

        virtual bool Scatter(const Ray& ray, const HitRecord& hitRecord, Color& outAttenuation, Ray& outScattered) const noexcept override;

    public:
        Color Albedo;
        float Fuzz;

    private:
        uint32_t mPadding;
    };

    constexpr Metal::Metal(const Color& albedo, float fuzz) noexcept
        : Albedo(albedo)
        , Fuzz(std::min(fuzz, 1.0f))
    {
    }
} // namespace ellie