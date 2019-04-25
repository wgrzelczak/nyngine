#include "pch.h"
#include "Input.h"
#include "Core\Engine.h"
#include "GLFW\glfw3.h"

namespace ny::Core
{
    Input* Input::GetInstance()
    {
        static Input instance;
        return &instance;
    }

    bool Input::IsKeyPressedImpl(i32 keyCode) const
    {
        auto window = Engine::GetInstance()->GetWindow().GetNative();
        return (glfwGetKey(window, keyCode) & (GLFW_PRESS | GLFW_REPEAT)) != 0;
    }

    bool Input::IsMouseButtonPressedImpl(i32 button) const
    {
        auto window = Engine::GetInstance()->GetWindow().GetNative();
        return (glfwGetMouseButton(window, button) & GLFW_PRESS) != 0;
    }

    std::pair<float, float> Input::GetMousePosImpl() const
    {
        double x, y;
        auto window = Engine::GetInstance()->GetWindow().GetNative();
        glfwGetCursorPos(window, &x, &y);

        return std::make_pair(static_cast<f32>(x), static_cast<f32>(y));
    }

    f32 Input::GetMousePosXImpl() const
    {
        auto [x, y] = GetMousePosImpl();
        return x;
    }

    f32 Input::GetMousePosYImpl() const
    {
        auto [x, y] = GetMousePosImpl();
        return y;
    }

} // namespace ny::Core
