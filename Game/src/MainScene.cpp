#include "pch.h"
#include "MainScene.h"
#include "Core\Input\Input.h"
#include "ECS\MeshRendererSystem.h"
#include "Scene\SceneLoader.h"

static glm::quat tmpQuat{1.f, 0.f, 0.f, 0.f};
static glm::quat tmpQuatN{1.f, 0.f, 0.f, 0.f};

void MainScene::Init()
{
    m_mainCamera = {{0, 0, -3.0f}, {0, 0, 1}, {0, 1, 0}};
    m_mainCamera.SetPerspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);

    m_ecs.reset(new Ecs());
    {
        auto loader = ny::SceneLoader("Assets/glTF/Duck/Duck.gltf", m_ecs);
        loader.LoadScene(this, 0);
    }

    ny::imgui::RegisterFunction(
        [this]() -> void {
            ImGui::DragFloat4("Rotation In Time", &tmpQuat.x, 0.0001f, -1.f, 1.f, "%.5f");
            tmpQuatN = glm::normalize(tmpQuat);

            ImGui::DragFloat3("Camera position", &m_mainCamera.GetPositionRef().x, 0.01f);
            ImGui::DragFloat3("Camera front", &m_mainCamera.GetFrontRef().x, 0.01f);

            m_mainCamera.UpdateView();
        });

    auto callback = [this]() -> void {
        for (const auto& o : m_objects)
        {
            o->ImGuiDraw();
        }
    };

    ny::imgui::RegisterWindow("Objects", callback);
}

void MainScene::Destroy()
{
    m_objects.clear();
}

void MainScene::Update()
{
    auto dt{ny::Core::Time::Delta() / 1000.f};
    const float speed{0.001f};
    if (ny::Core::Input::IsKeyPressed(NY_KEY_W))
        m_mainCamera.GetPositionRef().z += speed * dt;
    if (ny::Core::Input::IsKeyPressed(NY_KEY_S))
        m_mainCamera.GetPositionRef().z -= speed * dt;
    if (ny::Core::Input::IsKeyPressed(NY_KEY_A))
        m_mainCamera.GetPositionRef().x += speed * dt;
    if (ny::Core::Input::IsKeyPressed(NY_KEY_D))
        m_mainCamera.GetPositionRef().x -= speed * dt;
    if (ny::Core::Input::IsKeyPressed(NY_KEY_Q))
        m_mainCamera.GetPositionRef().y += speed * dt;
    if (ny::Core::Input::IsKeyPressed(NY_KEY_E))
        m_mainCamera.GetPositionRef().y -= speed * dt;

    m_mainCamera.UpdateView();

    m_ecs->GetSystemManager()->Update();

    f32 delta = (float)ny::Core::Time::Delta() * 0.0001f;
    m_objects[0]->m_transform.AddRotation(tmpQuatN * delta);
}
