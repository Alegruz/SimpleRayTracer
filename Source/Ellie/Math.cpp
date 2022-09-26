#include "Math.h"

namespace ellie
{
    namespace Math
    {
        Vector3f GetRandomUnitSphereVector3f() noexcept
        {
            while (true)
            {
                Vector3f vec = GetRandomVector3f(-1.0f, 1.0f);

                if (vec.GetLengthSquared() >= 1.0f)
                {
                    continue;
                }

                return vec;
            }
        }

        Vector3f GetRandomUnitVector3f() noexcept
        {
            Vector3f vec = GetRandomUnitSphereVector3f();
            vec.Normalize();
            return vec;
        }

        Vector3f GetRandomUnitDiskVector3f() noexcept
        {
            while (true)
            {
                Vector3f vec = Vector3f(GetRandom(-1.0f, 1.0f), GetRandom(-1.0f, 1.0f), 0.0f);

                if (vec.GetLengthSquared() >= 1.0f)
                {
                    continue;
                }

                return vec;
            }
        }   
    }
}