#pragma once
#include "KeyboardDefines.h"
#include "MouseDefines.h"
#include "Preinclude.h"

namespace ny::Core
{
    class Input
    {
      public:
        static bool IsKeyPressed(i32 keyCode) { return GetInstance()->IsKeyPressedImpl(keyCode); }
        static bool IsMouseButtonPressed(i32 button) { return GetInstance()->IsMouseButtonPressedImpl(button); }
        static std::pair<float, float> GetMousePos() { return GetInstance()->GetMousePosImpl(); }
        static f32 GetMousePosX() { return GetInstance()->GetMousePosXImpl(); }
        static f32 GetMousePosY() { return GetInstance()->GetMousePosYImpl(); }

      private:
        static Input* GetInstance();

        bool IsKeyPressedImpl(i32 keyCode) const;
        bool IsMouseButtonPressedImpl(i32 button) const;
        std::pair<float, float> GetMousePosImpl() const;
        f32 GetMousePosXImpl() const;
        f32 GetMousePosYImpl() const;
    };
} // namespace ny::Core