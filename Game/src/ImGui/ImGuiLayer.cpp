#include "pch.h"
#include "ImGuiLayer.h"
#include "Core\Application.h"
#include "glad\glad.h" //to remove
#include "imgui.h"
#include "imgui_impl_opengl3.h"

namespace ny
{
    ImGuiLayer::ImGuiLayer() :
        m_time(0.0f)
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.KeyMap[ImGuiKey_Tab] = NY_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = NY_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = NY_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = NY_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = NY_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = NY_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = NY_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = NY_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = NY_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = NY_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = NY_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = NY_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = NY_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = NY_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = NY_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = NY_KEY_A;
        io.KeyMap[ImGuiKey_C] = NY_KEY_C;
        io.KeyMap[ImGuiKey_V] = NY_KEY_V;
        io.KeyMap[ImGuiKey_X] = NY_KEY_X;
        io.KeyMap[ImGuiKey_Y] = NY_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = NY_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnEnable()
    {
    }

    void ImGuiLayer::OnDisable()
    {
    }

    void ImGuiLayer::OnUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();

        io.DisplaySize = ImVec2(IApp->GetWindow().GetWidth(), IApp->GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
        m_time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Core::WindowResizedEvent e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.width, e.height);
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, e.width, e.height); //to remove
    }

    void ImGuiLayer::OnEvent(Core::KeyPressedEvent e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.keyCode] = true;

        io.KeyCtrl = io.KeysDown[NY_KEY_LEFT_CONTROL] || io.KeysDown[NY_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[NY_KEY_LEFT_SHIFT] || io.KeysDown[NY_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[NY_KEY_LEFT_ALT] || io.KeysDown[NY_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[NY_KEY_LEFT_SUPER] || io.KeysDown[NY_KEY_RIGHT_SUPER];
    }

    void ImGuiLayer::OnEvent(Core::KeyReleasedEvent e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.keyCode] = true;
    }

    void ImGuiLayer::OnEvent(Core::KeyTypedEvent e)
    {
        ImGuiIO& io = ImGui::GetIO();
        int keycode = e.keyCode;
        if (keycode > 0 && keycode < 0x10000)
            io.AddInputCharacter((unsigned short)keycode);
    }

    void ImGuiLayer::OnEvent(Core::MouseButtonPressedEvent e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.keyCode] = true;
    }

    void ImGuiLayer::OnEvent(Core::MouseButtonReleasedEvent e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.keyCode] = false;
    }

    void ImGuiLayer::OnEvent(Core::MouseMovedEvent e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.x, e.y);
    }

    void ImGuiLayer::OnEvent(Core::MouseScrolledEvent e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.x;
        io.MouseWheel += e.y;
    }
} // namespace ny