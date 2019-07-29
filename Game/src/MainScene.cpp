#include "pch.h"
#include "MainScene.h"
#include "ECS\MeshRendererSystem.h"
#include "Rendering\ModelLoader.h"
#include "Scene\SceneLoader.h"

static glm::quat tmpQuat{1.f, 0.f, 0.f, 0.f};
static glm::quat tmpQuatN{1.f, 0.f, 0.f, 0.f};

void MainScene::Init()
{
    m_ecs.reset(new Ecs());
    {
        //auto loader = ny::SceneLoader("Assets/glTF/Duck/Duck.gltf", m_ecs);

        auto loader = ny::SceneLoader("Assets/glTF/RiggedFigure/RiggedFigure.gltf", m_ecs);

        loader.LoadScene(this, 0);
    }

    //m_objects[0]->m_transform.SetScale({50, 50, 50});
    // m_objects[0]->m_transform.SetRotation({0, 0, 0, 1});

    //m_objects[0]->m_transform.SetScale({0.01, 0.01, 0.01});

    ny::imgui::RegisterFunction(
        [this]() -> void {
            ImGui::DragFloat4("Rotation In Time", &tmpQuat.x, 0.0001f, -1.f, 1.f, "%.5f");
            tmpQuatN = glm::normalize(tmpQuat);
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
    m_ecs->GetSystemManager()->Update();

    f32 delta = (float)ny::Core::Time::Delta() * 0.0001f;
    m_objects[0]->m_transform.AddRotation(tmpQuatN * delta);
}
