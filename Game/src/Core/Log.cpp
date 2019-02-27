#include "pch.h"
#include "Log.h"

namespace ny::Core
{
    std::shared_ptr<spdlog::logger> Log::m_coreLogger;

    void Log::Init()
    {
        m_coreLogger = spdlog::stdout_color_mt("Core");
        m_coreLogger->set_level(spdlog::level::trace);
        m_coreLogger->set_pattern("%^[%T] [%n] %v%$");

        m_coreLogger->trace("Logger initialized");
    }

    std::shared_ptr<spdlog::logger> Log::Core()
    {
        return m_coreLogger;
    }

} // namespace ny::Core