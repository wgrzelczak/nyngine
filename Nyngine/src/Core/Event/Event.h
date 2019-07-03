#pragma once
#include "Preinclude.h"

#define EVENT_REGISTER_TYPE(type)                                  \
    static EventType GetStaticType() { return EventType::##type; } \
    virtual EventType GetEventType() const override { return GetStaticType(); }

#define EVENT_DISPATCH(listener, event, EventClass)            \
    using ListenerType = std::decay_t<decltype(listener)>;     \
    if (event.GetEventType() == EventClass::GetStaticType())   \
    {                                                          \
        if constexpr (HasEvent<ListenerType, EventClass>)      \
        {                                                      \
            listener.OnEvent(static_cast<EventClass&>(event)); \
        }                                                      \
        return;                                                \
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

        const EventType m_type{EventType::Undefined};
        bool m_handled{false};
    };
} // namespace ny::Core