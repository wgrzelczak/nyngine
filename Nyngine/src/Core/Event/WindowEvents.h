#pragma once
#include "Event.h"

namespace ny::Core
{
    struct WindowClosedEvent : Event
    {
        WindowClosedEvent() :
            Event(EventType::WindowClosedEvent) {}

		EVENT_REGISTER_TYPE(WindowClosedEvent);
    };

    struct WindowResizedEvent : Event
    {
        WindowResizedEvent(i32 width, i32 heigh) :
            Event(EventType::WindowClosedEvent), width(width), height(height) {}
        const i32 width;
        const i32 height;

		EVENT_REGISTER_TYPE(WindowResizedEvent);
    };

} // namespace ny::Core