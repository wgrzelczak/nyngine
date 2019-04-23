#pragma once
#include "Preinclude.h"

#define EVENT_REGISTER_TYPE(type)                                  \
    static EventType GetStaticType() { return EventType::##type; } \
    virtual EventType GetEventType() const override { return GetStaticType(); }

#define EVENT_DISPATCH(listener, event, EventClass)              \
    using ListenerType = std::decay_t<decltype(listener)>;       \
    if constexpr (HasEvent<ListenerType, EventClass>)            \
    {                                                            \
        if (event.GetEventType() == EventClass::GetStaticType()) \
        {                                                        \
            listener.OnEvent(static_cast<EventClass&>(event));   \
        }                                                        \
    }

namespace ny::Core
{
    enum class EventType
    {
        Undefined,

        WindowClosedEvent,
        WindowResizedEvent,

        KeyPressedEvent,
        KeyReleasedEvent,
        KeyTypedEvent,

        MouseButtonPressedEvent,
        MouseButtonReleasedEvent,
        MouseScrolledEvent,
        MouseMovedEvent
    };

    struct Event abstract
    {
        Event(EventType type) :
            m_type(type), m_handled(false) {}

        virtual EventType GetEventType() const = 0;

        const EventType m_type;
        bool m_handled;
    };
} // namespace ny::Core