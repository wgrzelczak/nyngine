#pragma once
#include "spdlog/spdlog.h"

namespace ny::Core
{
    class Log
    {
    public:
        static void Init(const std::string& name);
        static void Deinit();

        static std::shared_ptr<spdlog::logger> Get();

    private:
        static std::shared_ptr<spdlog::logger> m_logger;
    };
} // namespace ny::Core
