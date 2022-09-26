#ifdef UNIX
#include <cfloat>
#endif

#include "Vector3f.h"

namespace ellie
{
    std::ostream& operator<<(std::ostream& os, const Vector3f& vector)
    {
        return os << vector.X << ' ' << vector.Y << ' ' << vector.Z;
    }

    Vector3f GetUnitVector(const Vector3f& vector) noexcept
    {
        return vector / vector.GetLength();
    }

    Vector3f Refract(const Vector3f& vector, const Vector3f& normal, float etaiOverEtat)
    {
        float cosTheta = fmin(Dot(-vector, normal), 1.0f);
        Vector3f rOutPerp = etaiOverEtat * (vector + cosTheta * normal);
        Vector3f rOutParallel = -sqrt(fabs(1.0f - rOutPerp.GetLengthSquared())) * normal;
        return rOutPerp + rOutParallel;
    }

    float Vector3f::GetLength() const noexcept
    {
        return std::sqrt(GetLengthSquared());
    }

    void Vector3f::Normalize()
    {
        assert(GetLengthSquared() > 0.0f);

        float length = GetLength();
        X /= length;
        Y /= length;
        Z /= length;
    }

    bool Vector3f::IsNearZero() const noexcept
    {
        constexpr const float eps = FLT_MIN;
        return (fabs(X) < eps) && (fabs(Y) < eps) && (fabs(Z) < eps);
    }
}