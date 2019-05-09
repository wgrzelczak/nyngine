#pragma once
#include "Preinclude.h"
#include "imgui.h"
#include "imgui_bridge.h"

namespace ny
{
    class ImGuiSystem
    {
    public:
        static ImGuiSystem* GetInstance();
        ~ImGuiSystem();

        void Update();
        void Clear();

        using Function = std::function<void()>;
        static void RegisterFunction(Function function);

    private:
        ImGuiSystem();

        void NewFrame();
        void EndFrame();

        void RegisterFunctionImpl(Function function);

        std::vector<Function> m_drawFunctions;
    };
} // namespace ny