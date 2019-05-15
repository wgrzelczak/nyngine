#pragma once
#include <cstdint>
#include <type_traits>

namespace id
{
    using Entity = uint32_t;
    using Component = uint32_t;
    using Event = uint32_t;
} // namespace id

enum class Priority : uint8_t
{
    UNDEFINED = 0,
    LOW = 64,
    MEDIUM = 128,
    HIGH = 192
};