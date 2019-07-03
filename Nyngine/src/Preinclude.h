#pragma once
#define NY_LOGGER() ny::Core::Log::Get()
#define NY_TRACE(...) NY_LOGGER()->trace(__VA_ARGS__);
#define NY_DEBUG(...) NY_LOGGER()->debug(__VA_ARGS__);
#define NY_INFO(...) NY_LOGGER()->info(__VA_ARGS__);
#define NY_WARN(...) NY_LOGGER()->warn(__VA_ARGS__);
#define NY_ERROR(...) NY_LOGGER()->error(__VA_ARGS__);
#define NY_CRITICAL_ERROR(...) NY_LOGGER()->critical(__VA_ARGS__);

#define NY_BREAK() __debugbreak();
#define NY_ASSERT(x, ...)      \
    if (!(x))                  \
    {                          \
        NY_ERROR(__VA_ARGS__); \
        NY_BREAK();            \
    }

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;
using f32 = float;

#define BIT_POSITION(pos) (1 << pos)
#define BIT_IS_SET(n, pos) ((n & BIT_POSITION(pos)) != 0)
#define BIT_ARE_SET(n, m) ((n & m) != 0)
#define BIT_SET(n, pos) n |= BIT_POSITION(pos)
#define BIT_CLEAR(n, pos) n &= ~BIT_POSITION(pos)
