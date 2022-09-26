#pragma once

#include "Pch.h"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define CPU_SINGLE_THREAD (0)
#define CPU_MULTI_THREAD (1)
#define GPU_CUDA (0)

#if GPU_CUDA
#include <cuda_runtime.h>

#include <helper_functions.h> // helper utility functions 
#include <helper_cuda.h>      // helper functions for CUDA error checking and initialization
#include <helper_math.h>

#include "CudaUtils.h"
#include "RayTracing.cuh"
#endif

#include "Camera.h"
#include "Color.h"
#include "Dielectric.h"
#include "HittableList.h"
#include "IHittable.h"
#include "IMaterial.h"
#include "Lambertian.h"
#include "Math.h"
#include "Metal.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vector3f.h"

namespace ellie
{
#if CPU_MULTI_THREAD
    static std::mutex sMutex;
#endif

    class RayTracer final
    {
    public:
        static constexpr const size_t MAX_BOUND_DEPTH = 3;

        static Color RayColor(const Ray& ray, const IHittable& world, size_t depth = MAX_BOUND_DEPTH) noexcept;

    public:
        explicit RayTracer() noexcept = delete;
        explicit RayTracer(size_t width, size_t height, size_t numChannels) noexcept;
        explicit RayTracer(const RayTracer& other) noexcept;
        explicit RayTracer(RayTracer&& other) noexcept;
        RayTracer& operator=(const RayTracer& other) noexcept;
        constexpr RayTracer& operator=(RayTracer&& other) noexcept;
        ~RayTracer() noexcept;

        void Initialize() noexcept;
        void Render() noexcept;

        static constexpr const size_t SAMPLES_PER_PIXEL = 1;

    private:
#if GPU_CUDA
        bool initializeCuda(GPU_SELECT_MODE mode, int32_t specifiedDeviceId) noexcept;
#endif
        static void renderSingleRow(uint8_t* backBuffer, size_t width, size_t height, size_t numChannels, size_t y, const Camera& camera, const HittableList& world) noexcept;
        static void renderSinglePixel(uint8_t* backBuffer, size_t width, size_t height, size_t numChannels, size_t x, size_t y, const Camera& camera, const HittableList& world) noexcept;

        static void createRandomScene(HittableList& outWorld, std::vector<IMaterial*>& outMaterials);

    private:
        // Image
        size_t mWidth;
        size_t mHeight;
        size_t mNumChannels;
        uint8_t* mHostBackBuffer;
#if GPU_CUDA
        uint8_t* mDeviceBackBuffer;
#endif

        // Camera
        Camera mCamera;

        uint32_t mPadding;

        // World
        HittableList mWorld;
        std::vector<IMaterial*> mMaterials;

#if GPU_CUDA
        // Cuda
        int32_t mCudaSelectedDeviceId;
        GPU_INFO mGpuInfo;
        BOOL mbCanPrefetch;
        CudaSphere* mHostSpheres;
        CudaSphere* mDeviceSpheres;
        size_t mNumSpheres;
#endif

#if CPU_MULTI_THREAD
        // Multi-Threading
        std::vector<std::thread> mThreadsPerRow;
#endif
    };

    constexpr RayTracer& RayTracer::operator=(RayTracer&& other) noexcept
    {
        if (this != &other)
        {
            mWidth = other.mWidth;
            mHeight = other.mHeight;
            mNumChannels = other.mNumChannels;
            mHostBackBuffer = other.mHostBackBuffer;
#if GPU_CUDA
            mDeviceBackBuffer = other.mDeviceBackBuffer;
#endif

            mCamera = std::move(other.mCamera);
            mWorld = std::move(other.mWorld);

            other.mWidth = 0;
            other.mHeight = 0;
            other.mNumChannels = 0;
            other.mHostBackBuffer = nullptr;
#if GPU_CUDA
            other.mDeviceBackBuffer = nullptr;
#endif
        }

        return *this;
    }
} // namespace ellie