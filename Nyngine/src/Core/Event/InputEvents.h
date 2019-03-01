#pragma once
#include "Core\Input\KeyboardDefines.h"
#include "Core\Input\MouseDefines.h"
#include "Event.h"

namespace ny::Core
{
    //Keyboard events
    struct KeyPressedEvent : Event
    {
        KeyPressedEvent(i32 key, i32 repeat) :
            Event(), keyCode(key), repeat(repeat) {}
        const i32 keyCode;
        const i32 repeat;
    };

    struct KeyReleasedEvent : Event
    {
        KeyReleasedEvent(i32 key) :
            Event(), keyCode(key) {}
        const i32 keyCode;
    };

    struct KeyTypedEvent : Event
    {
        KeyTypedEvent(u32 key) :
            Event(), keyCode(key) {}
        const u32 keyCode;
    };

    //Mouse events
    struct MouseButtonPressedEvent : Event
    {
        MouseButtonPressedEvent(i32 key) :
            Event(), keyCode(key) {}
        const i32 keyCode;
    };

    struct MouseButtonReleasedEvent : Event
    {
        MouseButtonReleasedEvent(i32 key) :
            Event(), keyCode(key) {}
        const i32 keyCode;
    };

    struct MouseScrolledEvent : Event
    {
        MouseScrolledEvent(f32 x, f32 y) :
            Event(), x(x), y(y) {}
        const f32 x;
        const f32 y;
    };

    struct MouseMovedEvent : Event
    {
        MouseMovedEvent(f32 x, f32 y) :
            Event(), x(x), y(y) {}
        const f32 x;
        const f32 y;
    };
} // namespace ny::Core