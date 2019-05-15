#pragma once
#include "EventBase.h"
#include "Preinclude.h"
#include <map>
#include <memory>

namespace engine::ecs
{
    template <class Data>
    class EventListener
    {
    public:
        EventListener() {}
        ~EventListener() {}

        virtual void operator()(const Data& sender) {}
    };
} // namespace engine::ecs