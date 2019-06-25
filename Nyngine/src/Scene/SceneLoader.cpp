#include "pch.h"
#include "SceneLoader.h"
#include "Ecs\MeshRendererComponent.h"
#include "Ecs\MeshRendererSystem.h"

#define GLTF_INVALID_INDEX (-1)
#define GLTF_KEY_ATTRIBUTE_POSITION "POSITION"
#define GLTF_KEY_ATTRIBUTE_NORMAL "NORMAL"
#define GLTF_KEY_ATTRIBUTE_TANGENT "TANGENT"
#define GLTF_KEY_ATTRIBUTE_TEXCOORD0 "TEXCOORD_0"
#define GLTF_KEY_ATTRIBUTE_TEXCOORD1 "TEXCOORD_1"
#define GLTF_KEY_ATTRIBUTE_COLOR0 "COLOR_0"
#define GLTF_KEY_ATTRIBUTE_JOINTS0 "JOINTS_0"
#define GLTF_KEY_ATTRIBUTE_WEIGHTS0 "WEIGHTS_0"

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
        //pos(x, y, z)
        transform.SetPosition({node.translation.at(0), node.translation.at(1), node.translation.at(2)});
        //quat(w, x, y, z)
        transform.SetRotation({node.rotation.at(3), node.rotation.at(0), node.rotation.at(1), node.rotation.at(2)});
        //scale(x, y, z)
        transform.SetScale({node.scale.at(0), node.scale.at(1), node.scale.at(2)});
    }

    void SceneLoader::LoadMesh(fx::gltf::Mesh& inMesh, EcsEntity* entity)
    {
        ny::Rendering::Mesh::VertexAttributesSettings settings;

        NY_DEBUG("Loading indices...")
        auto accessorId = inMesh.primitives[0].indices;
        GetAccessorData(accessorId, settings.indices);

        NY_DEBUG("Loading positions...")
        accessorId = inMesh.primitives[0].attributes[GLTF_KEY_ATTRIBUTE_POSITION];
        GetAccessorData(accessorId, settings.positions);

        NY_DEBUG("Loading normals...")
        accessorId = inMesh.primitives[0].attributes[GLTF_KEY_ATTRIBUTE_NORMAL];
        GetAccessorData(accessorId, settings.normals);

        ny::Rendering::Mesh* mesh = new ny::Rendering::Mesh();

        mesh->Generate(settings);

        auto sys = Ecs::GetSystemManager()->GetSystem<ECS::MeshRendererSystem>();

        auto component = entity->GetComponent<ny::ECS::MeshRendererComponent>();
        if (!component)
        {
            component = entity->AddComponent<ny::ECS::MeshRendererComponent>();
        }

        sys->RegisterEntity(entity);

        component->m_material = new ny::Rendering::Material("Assets/Shaders/pos.vs", "Assets/Shaders/uv.fs", "Assets/Textures/debug.jpeg");
        component->m_mesh = mesh;
    }

    void SceneLoader::GetAccessorData(i32 accessorId, Mesh::VertexAttributesSettings::Data& data)
    {
        if (accessorId == GLTF_INVALID_INDEX)
        {
            return;
        }

        NY_ASSERT(accessorId < m_doc.accessors.size(), "Error! Invalid gltf id");

        fx::gltf::Accessor& accessor{m_doc.accessors.at(accessorId)};

        switch (accessor.componentType)
        {
        case fx::gltf::Accessor::ComponentType::None:
            data.fieldsTypeSize = 0;
            break;
        case fx::gltf::Accessor::ComponentType::Byte:
        case fx::gltf::Accessor::ComponentType::UnsignedByte:
            data.fieldsTypeSize = 1;
            break;
        case fx::gltf::Accessor::ComponentType::Short:
        case fx::gltf::Accessor::ComponentType::UnsignedShort:
            data.fieldsTypeSize = 2;
            break;
        case fx::gltf::Accessor::ComponentType::UnsignedInt:
        case fx::gltf::Accessor::ComponentType::Float:
            data.fieldsTypeSize = 4;
            break;
        }

        data.num = accessor.count;
        switch (accessor.type)
        {
        case fx::gltf::Accessor::Type::None:
            data.fieldsNum = 0;
            break;
        case fx::gltf::Accessor::Type::Scalar:
            data.fieldsNum = 1;
            break;
        case fx::gltf::Accessor::Type::Vec2:
            data.fieldsNum = 2;
            break;
        case fx::gltf::Accessor::Type::Vec3:
            data.fieldsNum = 3;
            break;
        case fx::gltf::Accessor::Type::Vec4:
            data.fieldsNum = 4;
            break;
        case fx::gltf::Accessor::Type::Mat2:
            data.fieldsNum = 4;
            break;
        case fx::gltf::Accessor::Type::Mat3:
            data.fieldsNum = 9;
            break;
        case fx::gltf::Accessor::Type::Mat4:
            data.fieldsNum = 16;
            break;
        }

        auto bufferViewId = accessor.bufferView;
        auto bufferViewByteOffset = accessor.byteOffset;
        auto bufferId = m_doc.bufferViews.at(bufferViewId).buffer;
        auto bufferOffset = m_doc.bufferViews.at(bufferViewId).byteOffset;
        auto bufferPointer = m_doc.buffers.at(bufferId).data.data();

        data.dataPtr = (bufferPointer + bufferOffset + bufferViewByteOffset);
    }

} // namespace ny