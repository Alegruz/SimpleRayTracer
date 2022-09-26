#include "Color.h"
#include "IHittable.h"
#include "IMaterial.h"
#include "Math.h"
#include "Ray.h"
#include "Vector3f.h"

namespace ellie
{
    class Lambertian : public IMaterial
    {
    public:
        explicit constexpr Lambertian() noexcept = delete;
        explicit constexpr Lambertian(const Color& albedo) noexcept;
        explicit constexpr Lambertian(const Lambertian& other) noexcept = default;
        explicit constexpr Lambertian(Lambertian&& other) noexcept = default;
        constexpr Lambertian& operator=(const Lambertian& other) noexcept = default;
        constexpr Lambertian& operator=(Lambertian&& other) noexcept = default;
        virtual ~Lambertian() noexcept = default;

        virtual bool Scatter(const Ray& ray, const HitRecord& hitRecord, Color& outAttenuation, Ray& outScattered) const noexcept override;

    public:
        Color Albedo;
    };

    constexpr Lambertian::Lambertian(const Color& albedo) noexcept
        : Albedo(albedo)
    {
    }
} // namespace ellie