#pragma once
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace ny::Core
{
    class Log
    {
      public:
        static void Init();
        static std::shared_ptr<spdlog::logger> Core();

      private:
        static std::shared_ptr<spdlog::logger> m_coreLogger;
    };
} // namespace ny::Core
