#pragma once
#include "Preinclude.h"
#include <chrono>

namespace ny::Core
{
    class Time
    {
    public:
        using ms = std::chrono::milliseconds;
        using us = std::chrono::microseconds;

        //template <class T = Ms>
        using Duration = std::chrono::duration<us>;
        using Clock = std::chrono::steady_clock;
        using TimePoint = std::chrono::time_point<Clock>;

        static void Init() { return GetInstance()->InitImpl(); }
        static void Update() { return GetInstance()->UpdateImpl(); }

        static TimePoint GetLocale() { return GetInstance()->GetLocaleImpl(); }
        static u64 DeltaFromStart() { return GetInstance()->DeltaFromStartImpl(); }
        static u64 Delta() { return GetInstance()->DeltaImpl(); }

        static us GetDuration(u32 time) { return us(time); }

    private:
        static Time* GetInstance();

        void InitImpl();
        void UpdateImpl();

        TimePoint GetLocaleImpl() const;
        u64 DeltaFromStartImpl() const;
        u64 DeltaImpl() const;

        TimePoint m_firstFrame;
        TimePoint m_lastFrame;
        TimePoint m_currentFrame;
    };
} // namespace ny::Core
