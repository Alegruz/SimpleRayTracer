#include <cstdint>
#include <iostream>

#include "Math.h"
#include "Vector3f.h"

namespace ellie
{
    typedef Vector3f Color;

    void WriteColor(std::ostream& os, const Color& pixelColor) noexcept;

    void WriteColor(std::ostream& os, const Color& pixelColor, size_t samplesPerPixel) noexcept;

    void WriteColor(uint8_t* pixels, const Color& pixelColor) noexcept;

    void WriteColor(uint8_t* pixels, const Color& pixelColor, size_t samplesPerPixel) noexcept;
}