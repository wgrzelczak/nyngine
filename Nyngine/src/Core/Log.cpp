#include "pch.h"
#include "Log.h"

namespace ny::Core
{
    std::shared_ptr<spdlog::logger> Log::m_logger{nullptr};

    void Log::Init(const std::string& name)
    {
        m_logger = spdlog::stdout_color_mt(name);
        m_logger->set_level(spdlog::level::trace);
        m_logger->set_pattern("%^[%T] [%n] %v%$");

        m_logger->trace("Logger initialized");
    }

    void Log::Deinit()
    {
        m_logger->trace("Logger deinitialized");
        m_logger.reset();
    }

    std::shared_ptr<spdlog::logger> Log::Get()
    {
        return m_logger;
    }

} // namespace ny::Core