#pragma once

#include <cstdint>
#include <random>

#include "Ray.h"
#include "Vector3f.h"

namespace ellie
{
    namespace Math
    {
        constexpr float Clamp(float value, float min, float max) noexcept;
        float GetRandom() noexcept;
	    float GetRandom(float min, float max) noexcept;
	    Vector3f GetRandomVector3f() noexcept;
	    Vector3f GetRandomVector3f(float min, float max) noexcept;
	    Vector3f GetRandomUnitSphereVector3f() noexcept;
	    Vector3f GetRandomUnitVector3f() noexcept;
	    Vector3f GetRandomUnitDiskVector3f() noexcept;
	    constexpr float Lerp(float lhs, float rhs, float scalar) noexcept;
	    constexpr Vector3f Lerp(const Vector3f& lhs, const Vector3f& rhs, float scalar) noexcept;

        inline constexpr float Clamp(float value, float min, float max) noexcept
        {
            if (value < min)
            {
                return min;
            }

            if (value > max)
            {
                return max;
            }

            return value;
        }

        inline float GetRandom() noexcept
        {
            return GetRandom(0.0f, 1.0f);
        }

        inline float GetRandom(float min, float max) noexcept
        {
            static std::uniform_real_distribution<float> sDistribution(min, max);
            static std::mt19937 sGenerator;

            return sDistribution(sGenerator);
        }

        inline Vector3f GetRandomVector3f() noexcept
        {
            return GetRandomVector3f(0.0f, 1.0f);
        }

        inline Vector3f GetRandomVector3f(float min, float max) noexcept
        {
            return Vector3f(GetRandom(min, max), GetRandom(min, max), GetRandom(min, max));
        }

        constexpr float Lerp(float lhs, float rhs, float scalar) noexcept
        {
            return (1.0f - scalar) * lhs + scalar * rhs;
        }

        constexpr Vector3f Lerp(const Vector3f& lhs, const Vector3f& rhs, float scalar) noexcept
        {
            return (1.0f - scalar) * lhs + scalar * rhs;
        }
    }
}