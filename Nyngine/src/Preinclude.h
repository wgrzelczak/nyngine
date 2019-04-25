#pragma once

#define NY_TRACE(...) Core::Log::Core()->trace(__VA_ARGS__);
#define NY_DEBUG(...) Core::Log::Core()->debug(__VA_ARGS__);
#define NY_INFO(...) Core::Log::Core()->info(__VA_ARGS__);
#define NY_WARN(...) Core::Log::Core()->warn(__VA_ARGS__);
#define NY_ERROR(...) Core::Log::Core()->error(__VA_ARGS__);
#define NY_CRITICAL_ERROR(...) Core::Log::Core()->critical__VA_ARGS__);

#define NY_BREAK() __debugbreak();
#define NY_ASSERT(x, ...)      \
    if (!x)                    \
    {                          \
        NY_ERROR(__VA_ARGS__); \
        NY_BREAK();            \
    }

using u32 = std::uint32_t;
using i32 = std::int32_t;
using f32 = float;