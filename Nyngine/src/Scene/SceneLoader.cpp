#include "pch.h"
#include "SceneLoader.h"
#include "Ecs\MeshRendererComponent.h"
#include "Ecs\MeshRendererSystem.h"

#define GLTF_INVALID_INDEX (-1)
#define GLTF_KEY_ATTRIBUTE_POSITION "POSITION"

namespace ny
{
    SceneLoader::SceneLoader(const std::string& filename)
    {
        NY_DEBUG("Loading {}...", filename);
        m_doc = fx::gltf::LoadFromText(filename);
    }

    SceneLoader::~SceneLoader()
    {
        NY_DEBUG("Unloaded");
    }

    EcsEntity* SceneLoader::CreateEntityByNodeIndex(i32 nodeId, bool withChildren)
    {
        fx::gltf::Node& node = m_doc.nodes.at(nodeId);

        EcsEntity* entity{new EcsEntity()};

        LoadTransform(node, entity->m_transform);

        if (node.mesh != GLTF_INVALID_INDEX)
        {
            NY_DEBUG("Loadig mesh...");
            NY_ASSERT(node.mesh < m_doc.meshes.size(), "Error! Invalid gltf id");
            LoadMesh(m_doc.meshes.at(node.mesh), entity);
        }

        return entity;
    }

    void SceneLoader::LoadTransform(fx::gltf::Node& node, ECS::Transform& transform)
    {
        transform.SetPosition({node.translation.at(0), node.translation.at(1), node.translation.at(2)});
        transform.SetRotation({node.rotation.at(0), node.rotation.at(1), node.rotation.at(2), node.rotation.at(3)});
        transform.SetScale({node.scale.at(0), node.scale.at(1), node.scale.at(2)});
    }

    void SceneLoader::LoadMesh(fx::gltf::Mesh& inMesh, EcsEntity* entity)
    {
        ny::Rendering::Mesh::VertexAttributesSettings settings;

        NY_DEBUG("Loading indices...")
        auto accessorId = inMesh.primitives[0].indices;
        GetAccessorData(accessorId, settings.m_indicesStride, settings.m_indicesNum, settings.p_indices);

        accessorId = inMesh.primitives[0].attributes[GLTF_KEY_ATTRIBUTE_POSITION];
        NY_DEBUG("Loading positions...")
        GetAccessorData(accessorId, settings.m_positionsStride, settings.m_positionsNum, settings.p_positions);

        ny::Rendering::Mesh* mesh = new ny::Rendering::Mesh();

        mesh->Generate(settings);

        auto sys = Ecs::GetSystemManager()->GetSystem<ECS::MeshRendererSystem>();

        auto component = entity->GetComponent<ny::ECS::MeshRendererComponent>();
        if (!component)
        {
            component = entity->AddComponent<ny::ECS::MeshRendererComponent>();
        }

        sys->RegisterEntity(entity);

        component->m_material = new ny::Rendering::Material("Assets/Shaders/pos.vs", "Assets/Shaders/unlit.fs", "Assets/Textures/debug.jpeg");
        component->m_mesh = mesh;
    }

    void SceneLoader::GetAccessorData(i32 accessorId, u8& elementSize, u32& elementsNum, void*& data)
    {
        if (accessorId == GLTF_INVALID_INDEX)
        {
            return;
        }

        NY_ASSERT(accessorId < m_doc.accessors.size(), "Error! Invalid gltf id");

        switch (m_doc.accessors.at(accessorId).componentType)
        {
        case fx::gltf::Accessor::ComponentType::None:
            elementSize = 0;
            break;
        case fx::gltf::Accessor::ComponentType::Byte:
        case fx::gltf::Accessor::ComponentType::UnsignedByte:
            elementSize = 1;
            break;
        case fx::gltf::Accessor::ComponentType::Short:
        case fx::gltf::Accessor::ComponentType::UnsignedShort:
            elementSize = 2;
            break;
        case fx::gltf::Accessor::ComponentType::UnsignedInt:
        case fx::gltf::Accessor::ComponentType::Float:
            elementSize = 4;
            break;
        }

        elementsNum = m_doc.accessors.at(accessorId).count;

        auto bufferViewId = m_doc.accessors.at(accessorId).bufferView;
        auto bufferViewByteOffset = m_doc.accessors.at(accessorId).byteOffset;
        auto bufferId = m_doc.bufferViews.at(bufferViewId).buffer;
        auto bufferOffset = m_doc.bufferViews.at(bufferViewId).byteOffset;
        auto bufferPointer = m_doc.buffers.at(bufferId).data.data();

        data = (bufferPointer + bufferOffset + bufferViewByteOffset);
    }

} // namespace ny