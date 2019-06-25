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
    auto box = loader.CreateEntityByNodeIndex(2);

    //    auto meshRendererSystem = Ecs::GetSystemManager()->RegisterSystem<ny::ECS::MeshRendererSystem>();
    //
    //    auto boxMeshRendererComponent = m_box.AddComponent<ny::ECS::MeshRendererComponent>();
    //    meshRendererSystem->RegisterEntity(&m_box);
    //
    //    //auto lightMeshRendererComponent = m_directionalLight.AddComponent<ny::ECS::MeshRendererComponent>();
    //    //   meshRendererSystem->RegisterEntity(&m_directionalLight);
    //
    //    ny::Rendering::Mesh* cube = new ny::Rendering::Mesh();
    //    ny::Rendering::ModelLoader::LoadObj(*cube, "");
    //
    //    boxMeshRendererComponent->m_material = new ny::Rendering::Material("Assets/Shaders/default.vs", "Assets/Shaders/default.fs", "Assets/Textures/debug.jpeg");
    //    boxMeshRendererComponent->m_mesh = cube;
    //
    //    //lightMeshRendererComponent->m_material = new ny::Rendering::Material("Assets/Shaders/default.vs", "Assets/Shaders/unlit.fs", "Assets/Textures/debug.jpeg");
    //    //   lightMeshRendererComponent->m_mesh = cube;
    //
    //    m_box.m_transform.SetPosition(glm::vec3{0, 0, 0});
    //    m_box.m_transform.SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
    //    m_box.m_transform.SetRotation(glm::quat(0.0f, 0.0f, 0.0f, 0.1f));
    //
    //    //m_directionalLight.m_transform.SetPosition(glm::vec3{-0.5f, 0.5f, 0});
    //    //   m_directionalLight.m_transform.SetScale(glm::vec3(0.3f, 0.3f, 0.3f));
    //    //   m_directionalLight.m_transform.SetRotation(glm::quat(0.0f, 0.0f, 0.0f, 1.f));
    //
    //    ny::ImGuiSystem::RegisterFunction(
    //        [this]() -> void {
    //            ImGui::DragFloat4("Model rotation", &m_box.m_transform.GetRotationRef().x, 0.01f);
    //            m_box.m_transform.NormalizeRotation();
    //            ImGui::DragFloat4("Rotate0", &tmpQuat.x, 0.0001f, -1.f, 1.f, "%.5f");
    //            tmpQuatN = glm::normalize(tmpQuat);
    //            ImGui::DragFloat4("Rotate1", &tmpQuatN.x, 0.01f);
    //        });
}

void MainScene::Destroy()
{
}

void MainScene::Update()
{
    f32 delta = (float)ny::Core::Time::Delta() * 0.0001f;
    m_box.m_transform.AddRotation(tmpQuatN * delta);
}
