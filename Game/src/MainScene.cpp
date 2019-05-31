#include "pch.h"
#include "MainScene.h"
#include "ECS\MeshRendererSystem.h"

static glm::quat tmpQuat{1.f, 0.f, 0.f, 0.f};
static glm::quat tmpQuatN{1.f, 0.f, 0.f, 0.f};

void MainScene::Init()
{
    auto meshRendererSystem = Ecs::GetSystemManager()->RegisterSystem<ny::ECS::MeshRendererSystem>();

    auto boxMeshRendererComponent = m_box.AddComponent<ny::ECS::MeshRendererComponent>();
    meshRendererSystem->RegisterEntity(&m_box);

    std::vector<glm::vec3> positions = {
        {-1.f, 1.f, 1.f},
        {1.f, 1.f, 1.f},
        {-1.f, -1.f, 1.f},
        {1.f, -1.f, 1.f},

        {-1.f, 1.f, -1.f},
        {1.f, 1.f, -1.f},
        {-1.f, -1.f, -1.f},
        {1.f, -1.f, -1.f}};

    std::vector<glm::vec2> uvs = {
        {0.0f, 1.0f},
        {1.0f, 1.0f},
        {0.0f, 0.0f},
        {1.0f, 0.0f},

        {0.0f, 1.0f},
        {1.0f, 1.0f},
        {0.0f, 0.0f},
        {1.0f, 0.0f}};

    std::vector<u32> indicies = {
        0, 1, 2, 1, 3, 2, //front
        4, 5, 6, 5, 7, 6, //back

        0, 1, 4, 1, 4, 5, //up
        2, 6, 3, 6, 3, 7, //down

        0, 2, 4, 2, 4, 6, //left
        1, 3, 5, 3, 5, 7  //right
    };

    ny::Rendering::Material* matTmp = new ny::Rendering::Material("Assets/Shaders/default.vs", "Assets/Shaders/default.fs", "Assets/Textures/texture.jpg");
    ny::Rendering::Mesh* meshTmp = new ny::Rendering::Mesh(positions, uvs, indicies);
    ny::Rendering::Model* modelTmp = new ny::Rendering::Model(matTmp, meshTmp);

    boxMeshRendererComponent->m_model.reset(modelTmp);

    boxMeshRendererComponent->m_model->SetPosition(glm::vec3{0, 0, 0});
    boxMeshRendererComponent->m_model->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
    //tmp_model->SetQuaternionRotation(glm::quat(0.8f, 0.0f, 0.0f, 0.6f));

    ny::ImGuiSystem::RegisterFunction(
        [this]() -> void {
            ImGui::DragFloat4("Model rotation", &m_box.GetComponent<ny::ECS::MeshRendererComponent>()->m_model->GetRotationRef().x, 0.01f);
            m_box.GetComponent<ny::ECS::MeshRendererComponent>()->m_model->NormalizeRotation();
            ImGui::DragFloat4("Rotate0", &tmpQuat.x, 0.0001f, -1.f, 1.f, "%.5f");
            tmpQuatN = glm::normalize(tmpQuat);
            ImGui::DragFloat4("Rotate1", &tmpQuatN.x, 0.01f);
        });
}

void MainScene::Destroy()
{
}

void MainScene::Update()
{
    f32 delta = (float)ny::Core::Time::Delta() * 0.0001f;
    m_box.GetComponent<ny::ECS::MeshRendererComponent>()->m_model->AddRotation(tmpQuatN * delta);
    m_box.GetComponent<ny::ECS::MeshRendererComponent>()->m_model->CalculateModelMatrix();
}
