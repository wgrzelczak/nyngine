#pragma once
#include "Event.h"

namespace ny::Core
{
    struct WindowClosedEvent : Event
    {
    };

    struct WindowResizedEvent : Event
    {
        WindowResizedEvent(i32 width, i32 heigh) :
            Event(), width(width), height(height) {}
        const i32 width;
        const i32 height;
    };

} // namespace ny::Core