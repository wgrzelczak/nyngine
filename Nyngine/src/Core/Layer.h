#pragma once

namespace ny::Core
{
    class Layer
    {
    public:
        void SetIsEnabled(bool value) { m_isEnabled = value; }
        bool IsEnabled() const { return m_isEnabled; }

    private:
        bool m_isEnabled = false;
    };
} // namespace ny::Core