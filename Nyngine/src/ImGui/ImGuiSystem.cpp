#include "pch.h"
#include "ImGuiSystem.h"
#include "Core\Engine.h"

namespace ny
{
    ImGuiSystem* ImGuiSystem::GetInstance()
    {
        static ImGuiSystem instance;
        return &instance;
    }

    ImGuiSystem::ImGuiSystem()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        GLFWwindow* window = ny::Core::Engine::GetInstance()->GetWindow().GetNative();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    ImGuiSystem::~ImGuiSystem()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiSystem::Update()
    {
        NewFrame();

        ImGui::Begin("Window");
        for (const auto& f : m_drawFunctions)
        {
            if (f) f();
        }
        ImGui::End();

        EndFrame();
    }

    void ImGuiSystem::Clear()
    {
        m_drawFunctions.clear();
    }

    void ImGuiSystem::RegisterFunction(Function function)
    {
        GetInstance()->RegisterFunctionImpl(function);
    }

    void ImGuiSystem::RegisterFunctionImpl(Function function)
    {
        m_drawFunctions.push_back(std::move(function));
    }

    void ImGuiSystem::NewFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiSystem::EndFrame()
    {
        ImGuiIO& io = ImGui::GetIO();

        io.DisplaySize = ImVec2(static_cast<f32>(Core::Engine::GetInstance()->GetWindow().GetWidth()), static_cast<f32>(Core::Engine::GetInstance()->GetWindow().GetHeight()));

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

} // namespace ny