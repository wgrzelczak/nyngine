#include "pch.h"
#include "ImGuiSystem.h"
#include "Core\Engine.h"

namespace ny::imgui
{
    void RegisterFunction(Function drawFunction)
    {
        ImGuiSystem::GetInstance()->RegisterFunction(drawFunction);
    }

    void RegisterWindow(std::string name, Function drawFunction, bool isOpened)
    {
        ImGuiSystem::GetInstance()->RegisterWindow(ImGuiWindow(name, drawFunction, 0, isOpened));
    }

    ImGuiSystem* ImGuiSystem::GetInstance()
    {
        static ImGuiSystem instance;
        return &instance;
    }

    ImGuiSystem::ImGuiSystem()
    {
        InitCore();
        m_mainWindow = std::make_unique<ImGuiWindow>(
            "ImGui",
            std::bind(&ImGuiSystem::MainWindowDrawFunction, this),
            ImGuiWindowFlags_MenuBar,
            true);
    }

    void ImGuiSystem::InitCore()
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
        {
            DrawWindows();
            DrawMainWindow();
        }
        EndFrame();
    }

    void ImGuiSystem::Clear()
    {
        m_drawFunctions.clear();
        m_windows.clear();
    }

    void ImGuiSystem::RegisterFunction(Function drawFunction)
    {
        m_drawFunctions.push_back(std::move(drawFunction));
    }

    void ImGuiSystem::RegisterWindow(ImGuiWindow window)
    {
        m_windows.push_back(std::move(window));
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

    void ImGuiSystem::DrawMainWindow()
    {
        m_mainWindow->Draw();
    }

    void ImGuiSystem::DrawWindows()
    {
        for (auto& w : m_windows)
        {
            w.Draw();
        }
    }

    void ImGuiSystem::MainWindowDrawFunction()
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Windows"))
            {
                for (auto& w : m_windows)
                {
                    if (ImGui::MenuItem(w.m_title.c_str(), nullptr, &w.m_isOpen)) {}
                }

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        for (const auto& f : m_drawFunctions)
        {
            if (f) f();
        }
    }

} // namespace ny::imgui