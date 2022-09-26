#pragma once

#include "Pch.h"

#include "Math.h"
#include "Ray.h"
#include "Vector3f.h"

namespace ellie
{
    class Camera final
    {
    public:
        explicit Camera() noexcept;
        explicit Camera(const Point3f& eye, const Point3f& at, const Vector3f& up, float vFov, float aspectRatio, float aperture) noexcept;
        explicit Camera(const Point3f& eye, const Point3f& at, const Vector3f& up, float vFov, float aspectRatio, float aperture, float focusDistance) noexcept;
        //explicit constexpr Camera(const Camera& other) noexcept = default;
        //explicit constexpr Camera(Camera&& other) noexcept = default;
        //constexpr Camera& operator=(const Camera& other) noexcept = default;
        //constexpr Camera& operator=(Camera&& other) noexcept = default;
        ~Camera() noexcept = default;

        Ray GetRay(float u, float v) const noexcept;

        constexpr const Point3f& GetPosition() const noexcept;
        constexpr const Vector3f& GetHorizontal() const noexcept;
        constexpr const Vector3f& GetVertical() const noexcept;
        constexpr const Vector3f& GetLowerLeftCorner() const noexcept;

    public:
        static constexpr const float ASPECT_RATIO = 16.0f / 9.0f;
        static constexpr const float VIEWPORT_HEIGHT = 2.0f;
        static constexpr const float VIEWPORT_WIDTH = ASPECT_RATIO * VIEWPORT_HEIGHT;
        static constexpr const float FOCAL_LENGTH = 1.0f;

    private:
        Point3f mEye;
        Vector3f mHorizontal;
        Vector3f mVertical;
        Point3f mLowerLeftCorner;

        Vector3f mU;
        Vector3f mV;
        Vector3f mW;
        float mLensRadius;
    };

    constexpr const Point3f& Camera::GetPosition() const noexcept
    {
        return mEye;
    }

    constexpr const Vector3f& Camera::GetHorizontal() const noexcept
    {
        return mHorizontal;
    }

    constexpr const Vector3f& Camera::GetVertical() const noexcept
    {
        return mHorizontal;
    }

    constexpr const Vector3f& Camera::GetLowerLeftCorner() const noexcept
    {
        return mLowerLeftCorner;
    }
} // namespace ellie