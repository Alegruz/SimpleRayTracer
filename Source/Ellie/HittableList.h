#pragma once

#include <cassert>
#include <cstdlib>
#include <memory>

#include "IHittable.h"

namespace ellie
{
    class HittableList final : public IHittable
    {
    public:
        //explicit constexpr HittableList() noexcept = default;
        //explicit constexpr HittableList(const std::shared_ptr<IHittable>& object) noexcept;
        //explicit constexpr HittableList(const HittableList& other) noexcept = default;
        //explicit constexpr HittableList(HittableList&& other) noexcept = default;
        //constexpr HittableList& operator=(const HittableList& other) noexcept = default;
        //constexpr HittableList& operator=(HittableList&& other) noexcept = default;
        ~HittableList() noexcept = default;

        void Clear() noexcept;
        void Add(const std::shared_ptr<IHittable>& object) noexcept;

        virtual bool HasHit(const Ray& ray, float minScalar, float maxScalar, HitRecord& outRecord) const noexcept override;

    public:
        static constexpr const size_t MAX_OBJECTS = 512;

        size_t Size;
        std::shared_ptr<IHittable> Objects[MAX_OBJECTS];
    };

    //constexpr HittableList::HittableList(const std::shared_ptr<IHittable>& object) noexcept
    //	: Objects()
    //{
    //	Add(object);
    //}
} // namespace ellie