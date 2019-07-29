#include "pch.h"
#include "SceneLoader.h"
#include "Ecs\MeshRendererComponent.h"
#include "Ecs\MeshRendererSystem.h"
#include <glm/gtx/matrix_decompose.hpp>

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
    SceneLoader::SceneLoader(const std::string& filename, EcsPtr ecs) :
        m_ecs(ecs)
    {
        NY_DEBUG("Loading {}...", filename);
        m_doc = fx::gltf::LoadFromText(filename);
    }

    SceneLoader::~SceneLoader()
    {
        NY_DEBUG("Unloaded");
    }

    void SceneLoader::LoadScene(Scene* scene, i32 sceneId)
    {
        for (const auto& n : m_doc.scenes.at(sceneId).nodes)
        {
            scene->m_objects.push_back(CreateEntityByNodeIndex(n));
        }
    }

    std::shared_ptr<EcsEntity> SceneLoader::CreateEntityByNodeIndex(i32 nodeId, bool withChildren)
    {
        auto entity = std::make_shared<EcsEntity>(m_ecs); //todo: move create to EcsManager
        entity->m_name = std::to_string(nodeId);

        fx::gltf::Node& node = m_doc.nodes.at(nodeId);
        LoadTransform(node, entity->m_transform);
        LoadMesh(node, entity);
        //LoadAnimation();

        if (withChildren)
        {
            for (const auto& n : node.children)
            {
                auto c = CreateEntityByNodeIndex(n);
                c->SetParent(entity);
                entity->AddChild(c);
            }
        }

        return entity;
    }

    void SceneLoader::LoadTransform(fx::gltf::Node& node, ECS::Transform& transform)
    {
        if (std::equal(std::begin(node.matrix), std::end(node.matrix), std::begin(fx::gltf::defaults::IdentityMatrix)))
        {
            //Matrix is not filled, load TRS

            //pos(x, y, z)
            transform.SetPosition({node.translation.at(0), node.translation.at(1), node.translation.at(2)});
            //quat(w, x, y, z)
            transform.SetRotation({node.rotation.at(3), node.rotation.at(0), node.rotation.at(1), node.rotation.at(2)});
            //scale(x, y, z)
            transform.SetScale({node.scale.at(0), node.scale.at(1), node.scale.at(2)});
        }
        else
        {
            const glm::mat4 matrix{
                node.matrix.at(0),
                node.matrix.at(1),
                node.matrix.at(2),
                node.matrix.at(3),
                node.matrix.at(4),
                node.matrix.at(5),
                node.matrix.at(6),
                node.matrix.at(7),
                node.matrix.at(8),
                node.matrix.at(9),
                node.matrix.at(10),
                node.matrix.at(11),
                node.matrix.at(12),
                node.matrix.at(13),
                node.matrix.at(14),
                node.matrix.at(15)};

            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;
            glm::vec3 skew;
            glm::vec4 perspective;
            glm::decompose(matrix, scale, rotation, translation, skew, perspective);

            transform.SetPosition(translation);
            transform.SetRotation(rotation);
            transform.SetScale(scale);
        }
    }

    void SceneLoader::LoadMesh(fx::gltf::Node& node, std::shared_ptr<EcsEntity> entity)
    {
        Rendering::Mesh* pMesh = nullptr;
        if (node.mesh == GLTF_INVALID_INDEX)
        {
            return;
        }

        NY_DEBUG("Loadig mesh...");
        NY_ASSERT(node.mesh < m_doc.meshes.size(), "Error! Invalid gltf id");
        pMesh = CreateMesh(m_doc.meshes.at(node.mesh));

        auto sys = m_ecs->GetSystemManager()->GetSystem<ECS::MeshRendererSystem>();
        auto component = entity->GetComponent<ECS::MeshRendererComponent>();
        if (!component)
        {
            component = entity->AddComponent<ECS::MeshRendererComponent>();
        }

        sys->RegisterEntity(entity.get());

        std::string img = "Assets/Textures/debug.jpeg";
        if (m_doc.images.size() > 0)
            img = "Assets/glTF/Duck/" + m_doc.images.at(0).uri;
        component->m_material = new Rendering::Material("Assets/Shaders/defaultJoints.vs", "Assets/Shaders/defaultColor.fs", img);
        component->m_mesh = pMesh;
    }

    void SceneLoader::LoadAnimation(fx::gltf::Node& node, std::shared_ptr<EcsEntity> entity)
    {
    }

    Rendering::Mesh* SceneLoader::CreateMesh(fx::gltf::Mesh& inMesh)
    {
        ny::Rendering::Mesh::VertexAttributesSettings settings;

        NY_DEBUG("Loading indices...");
        auto accessorId = inMesh.primitives[0].indices;
        GetAccessorData(accessorId, settings.indices);

        NY_DEBUG("Loading positions...");
        accessorId = inMesh.primitives[0].attributes[GLTF_KEY_ATTRIBUTE_POSITION];
        GetAccessorData(accessorId, settings.positions);

        NY_DEBUG("Loading normals...");
        accessorId = inMesh.primitives[0].attributes[GLTF_KEY_ATTRIBUTE_NORMAL];
        GetAccessorData(accessorId, settings.normals);

        NY_DEBUG("Loading texcoords0...");
        accessorId = inMesh.primitives[0].attributes[GLTF_KEY_ATTRIBUTE_TEXCOORD0];
        GetAccessorData(accessorId, settings.texcoords);

        NY_DEBUG("Loading joints0...");
        accessorId = inMesh.primitives[0].attributes[GLTF_KEY_ATTRIBUTE_JOINTS0];
        GetAccessorData(accessorId, settings.joints);

        NY_DEBUG("Loading weights0...");
        accessorId = inMesh.primitives[0].attributes[GLTF_KEY_ATTRIBUTE_WEIGHTS0];
        GetAccessorData(accessorId, settings.weights);

        NY_DEBUG("Loading jointMatrices...");

        return new ny::Rendering::Mesh(settings);
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