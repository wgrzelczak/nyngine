#pragma once
#include "Event.h"

namespace ny::ECS::Core
{
    template <class Data>
    class EventListener
    {
    public:
        virtual void operator()(const Data& sender) {}
    };
} // namespace ny::ECS::Core