#include "pch.h"
#include "MainScene.h"
#include "ECS\MeshRendererSystem.h"
#include "Rendering\ModelLoader.h"
#include "Scene\SceneLoader.h"

static glm::quat tmpQuat{1.f, 0.f, 0.f, 0.f};
static glm::quat tmpQuatN{1.f, 0.f, 0.f, 0.f};

void MainScene::Init()
{
    auto loader = ny::SceneLoader("Assets/glTF/Duck/Duck.gltf");
    m_box = loader.CreateEntityByNodeIndex(2);
    m_box->m_transform.SetScale({0.01, 0.01, 0.01});

    ny::ImGuiSystem::RegisterFunction(
        [this]() -> void {
            if (ImGui::Begin("Transform"))
            {
                ImGui::DragFloat3("Position", &m_box->m_transform.GetPositionRef().x, 0.01f);
                ImGui::DragFloat4("Rotation", &m_box->m_transform.GetRotationRef().x, 0.01f);
                ImGui::DragFloat3("Scale", &m_box->m_transform.GetScaleRef().x, 0.01f);

                m_box->m_transform.NormalizeRotation();
                ImGui::DragFloat4("Rotation In Time", &tmpQuat.x, 0.0001f, -1.f, 1.f, "%.5f");
                tmpQuatN = glm::normalize(tmpQuat);

                ImGui::End();
            }
        });
}

void MainScene::Destroy()
{
    if (m_box != nullptr)
        delete m_box;
}

void MainScene::Update()
{
    f32 delta = (float)ny::Core::Time::Delta() * 0.0001f;
    m_box->m_transform.AddRotation(tmpQuatN * delta);
}
