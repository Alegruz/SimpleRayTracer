#include "HittableList.h"

#include <cstring>

namespace ellie
{
    void HittableList::Clear() noexcept
    {
        //Objects.clear();
        // memset(Objects, 0, MAX_OBJECTS * sizeof(Objects[0]));
        for (uint32_t i = 0; i < MAX_OBJECTS; ++i)
        {
            Objects[i] = nullptr;
        }
    }

    void HittableList::Add(const std::shared_ptr<IHittable>& object) noexcept
    {
        //Objects.push_back(object);
        assert(Size < MAX_OBJECTS);
        Objects[Size++] = object;
    }

    bool HittableList::HasHit(const Ray& ray, float minScalar, float maxScalar, HitRecord& outRecord) const noexcept
    {
        HitRecord tempRecord;
        bool bHasHitAnything = false;
        float closestSoFar = maxScalar;

        for (size_t objectIdx = 0; objectIdx < Size; ++objectIdx)
        //for (IHittable* object : Objects)
        {
            if (Objects[objectIdx]->HasHit(ray, minScalar, maxScalar, tempRecord))
            {
                bHasHitAnything = true;
                if (closestSoFar > tempRecord.Scalar)
                {
                    closestSoFar = tempRecord.Scalar;
                    outRecord = tempRecord;
                }
            }
        }

        return bHasHitAnything;
    }
} // namespace ellie