#pragma once

namespace ny
{
    class Component
    {
    public:
        Component();
        ~Component();

        virtual void Update();
    };
} // namespace ny