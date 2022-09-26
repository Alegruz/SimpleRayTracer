#pragma once

#include <cassert>
#include <cmath>
#include <iostream>

namespace ellie
{
    class Vector3f final
    {
    public:
        explicit constexpr Vector3f() noexcept;
        explicit constexpr Vector3f(float x, float y, float z) noexcept;
        //explicit constexpr Vector3f(const Vector3f& other) noexcept = default;
        //explicit constexpr Vector3f(Vector3f&& other) noexcept = default;
        //constexpr Vector3f& operator=(const Vector3f& other) noexcept = default;
        //constexpr Vector3f& operator=(Vector3f&& other) noexcept = default;
        ~Vector3f() noexcept = default;

        constexpr Vector3f operator-() const noexcept;
        constexpr float operator[](size_t index) const noexcept;
        constexpr float& operator[](size_t index) noexcept;

        constexpr Vector3f& operator+=(const Vector3f& vector) noexcept;
        constexpr Vector3f& operator*=(const float scalar) noexcept;
        constexpr Vector3f& operator/=(const float scalar) noexcept;

        float GetLength() const noexcept;
        constexpr float GetLengthSquared() const noexcept;
        void Normalize();
        bool IsNearZero() const noexcept;

        float X;
        float Y;
        float Z;

    private:
        float mPadding = 0.0f;
    };

    typedef Vector3f Point3f;

    std::ostream& operator<<(std::ostream& os, const Vector3f& vector);

    constexpr Vector3f operator+(const Vector3f& lhs, const Vector3f& rhs) noexcept
    {
        return Vector3f(lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z);
    }

    constexpr Vector3f operator-(const Vector3f& lhs, const Vector3f& rhs) noexcept
    {
        return Vector3f(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z);
    }

    constexpr Vector3f operator*(const Vector3f& lhs, const Vector3f& rhs) noexcept
    {
        return Vector3f(lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z);
    }

    constexpr Vector3f operator*(float scalar, const Vector3f& vector) noexcept
    {
        return Vector3f(scalar * vector.X, scalar * vector.Y, scalar * vector.Z);
    }

    constexpr Vector3f operator*(const Vector3f& vector, float scalar) noexcept
    {
        return scalar * vector;
    }

    constexpr Vector3f operator/(const Vector3f& vector, float scalar) noexcept
    {
        return (1.0f / scalar) * vector;
    }

    constexpr float Dot(const Vector3f& lhs, const Vector3f& rhs) noexcept
    {
        return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
    }

    constexpr Vector3f Cross(const Vector3f& lhs, const Vector3f& rhs) noexcept
    {
        return Vector3f(
            lhs.Y * rhs.Z - lhs.Z * rhs.Y,
            lhs.Z * rhs.X - lhs.X * rhs.Z,
            lhs.X * rhs.Y - lhs.Y * rhs.X
        );
    }

    Vector3f GetUnitVector(const Vector3f& vector) noexcept;

    constexpr Vector3f Reflect(const Vector3f& vector, const Vector3f& normal)
    {
        return vector - 2.0f * Dot(vector, normal) * normal;
    }

    Vector3f Refract(const Vector3f& vector, const Vector3f& normal, float etaiOverEtat);

    constexpr Vector3f::Vector3f() noexcept
        : X(0.0f)
        , Y(0.0f)
        , Z(0.0f)
    {
    }

    constexpr Vector3f::Vector3f(float x, float y, float z) noexcept
        : X(x)
        , Y(y)
        , Z(z)
    {
    }

    constexpr Vector3f Vector3f::operator-() const noexcept
    {
        return Vector3f(-X, -Y, -Z);
    }

    constexpr float Vector3f::operator[](size_t index) const noexcept
    {
        assert(index < 3);

        return (&X)[index];
    }

    constexpr float& Vector3f::operator[](size_t index) noexcept
    {
        assert(index < 3);

        return (&X)[index];
    }

    constexpr Vector3f& Vector3f::operator+=(const Vector3f& vector) noexcept
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;

        return *this;
    }

    constexpr Vector3f& Vector3f::operator*=(const float scalar) noexcept
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;

        return *this;
    }

    constexpr Vector3f& Vector3f::operator/=(const float scalar) noexcept
    {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;

        return *this;
    }

    constexpr float Vector3f::GetLengthSquared() const noexcept
    {
        return X * X + Y * Y + Z * Z;
    }
}