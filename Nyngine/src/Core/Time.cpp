#pragma once
#include "pch.h"
#include "Time.h"

namespace ny::Core
{
    Time* Time::GetInstance()
    {
        static Time instance;
        return &instance;
    }

    void Time::InitImpl()
    {
        m_firstFrame = Clock::now();
        m_lastFrame = Clock::now();
        m_currentFrame = Clock::now();
    }

    void Time::UpdateImpl()
    {
        m_lastFrame = m_currentFrame;
        m_currentFrame = Clock::now();
    }

    Time::TimePoint Time::GetLocaleImpl() const
    {
        return Clock::now();
    }

    u64 Time::DeltaFromStartImpl() const
    {
        return std::chrono::duration_cast<us>(m_currentFrame - m_firstFrame).count();
    }

    u64 Time::DeltaImpl() const
    {
        return std::chrono::duration_cast<us>(m_currentFrame - m_lastFrame).count();
    }
} // namespace ny::Core
