#pragma once
#include "Event.h"
#include "Preinclude.h"

namespace ny::Ecs
{
    template <class Data>
    class EventListener
    {
    public:
        virtual void operator()(const Data& sender) {}
    };
} // namespace ny::Ecs