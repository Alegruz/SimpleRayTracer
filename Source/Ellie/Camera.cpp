#include "Camera.h"

namespace ellie
{
    Camera::Camera() noexcept
        : Camera(Point3f(-2.0f, 2.0f, 1.0f), Point3f(0.0f, 0.0f, -1.0f), Point3f(0.0f, 1.0f, 0.0f), 20.0f, Camera::ASPECT_RATIO, 2.0f)
    {
    }

    Camera::Camera(const Point3f& eye, const Point3f& at, const Vector3f& up, float vFov, float aspectRatio, float aperture) noexcept
        : Camera(eye, at, up, vFov, aspectRatio, aperture, (eye - at).GetLength())
    {
    }

    Camera::Camera(const Point3f& eye, const Point3f& at, const Vector3f& up, float vFov, float aspectRatio, float aperture, float focusDistance) noexcept
    {
        float theta = ConvertDegreesToRadians(vFov);
        float h = tan(theta / 2.0f);
        float viewportHeight = 2.0f * h;
        float viewportWidth = aspectRatio * viewportHeight;

        mW = GetUnitVector(eye - at);
        mU = GetUnitVector(Cross(up, mW));
        mV = Cross(mW, mU);

        mEye = eye;
        mHorizontal = focusDistance * viewportWidth * mU;
        mVertical = focusDistance * viewportHeight * mV;
        mLowerLeftCorner = mEye - (mHorizontal / 2.0f) - (mVertical / 2.0f) - focusDistance * mW;

        mLensRadius = aperture / 2.0f;
    }

    Ray Camera::GetRay(float u, float v) const noexcept
    {
        Vector3f rd = mLensRadius * Math::GetRandomUnitDiskVector3f();
        Vector3f offset = mU * rd.X + mV * rd.Y;

        return Ray(mEye + offset, mLowerLeftCorner + u * mHorizontal + v * mVertical - mEye - offset);
    }
} // namespace ellie