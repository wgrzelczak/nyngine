#pragma once
#include "Core\Input\KeyboardDefines.h"
#include "Core\Input\MouseDefines.h"
#include "Event.h"
#include <variant>

namespace ny::Core
{
    //Keyboard events
    struct KeyPressedEvent : Event
    {
        KeyPressedEvent(i32 key, i32 repeat) :
            Event(EventType::KeyPressedEvent), keyCode(key), repeat(repeat) {}
        const i32 keyCode;
        const i32 repeat;

		EVENT_REGISTER_TYPE(KeyPressedEvent);
    };

    struct KeyReleasedEvent : Event
    {
        KeyReleasedEvent(i32 key) :
            Event(EventType::KeyReleasedEvent), keyCode(key) {}
        const i32 keyCode;

		EVENT_REGISTER_TYPE(KeyReleasedEvent);
    };

    struct KeyTypedEvent : Event
    {
        KeyTypedEvent(u32 key) :
            Event(EventType::KeyTypedEvent), keyCode(key) {}
        const u32 keyCode;

		EVENT_REGISTER_TYPE(KeyTypedEvent);
    };

    //Mouse events
    struct MouseButtonPressedEvent : Event
    {
        MouseButtonPressedEvent(i32 key) :
            Event(EventType::MouseButtonPressedEvent), keyCode(key) {}
        const i32 keyCode;

		EVENT_REGISTER_TYPE(MouseButtonPressedEvent);
    };

    struct MouseButtonReleasedEvent : Event
    {
        MouseButtonReleasedEvent(i32 key) :
            Event(EventType::MouseButtonReleasedEvent), keyCode(key) {}
        const i32 keyCode;

		EVENT_REGISTER_TYPE(MouseButtonReleasedEvent);
    };

    struct MouseScrolledEvent : Event
    {
        MouseScrolledEvent(f32 x, f32 y) :
            Event(EventType::MouseScrolledEvent), x(x), y(y) {}
        const f32 x;
        const f32 y;

		EVENT_REGISTER_TYPE(MouseScrolledEvent);
    };

    struct MouseMovedEvent : Event
    {
        MouseMovedEvent(f32 x, f32 y) :
            Event(EventType::MouseMovedEvent), x(x), y(y) {}
        const f32 x;
        const f32 y;

		EVENT_REGISTER_TYPE(MouseMovedEvent);
    };
} // namespace ny::Core