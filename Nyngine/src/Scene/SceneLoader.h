#pragma once
#include "ECS/Ecs.h"
#include "Rendering/Mesh.h"
#include "Scene.h"
#include "fx/gltf.h"

namespace ny
{
    class SceneLoader
    {
    public:
        SceneLoader(const std::string& filename, EcsPtr ecs);
        ~SceneLoader();

        void LoadScene(Scene* scene, i32 sceneId);
        std::shared_ptr<EcsEntity> CreateEntityByNodeIndex(i32 nodeId, bool withChildren = true);

    private:
        void LoadTransform(fx::gltf::Node& node, ECS::Transform& transform);
        void AddMesh(fx::gltf::Node& node, std::shared_ptr<EcsEntity> entity);
        Rendering::Mesh* LoadMesh(fx::gltf::Mesh& inMesh);
        void GetAccessorData(i32 accessorId, Rendering::Mesh::VertexAttributesSettings::Data& data);

        EcsPtr m_ecs;
        fx::gltf::Document m_doc;
    };
} // namespace ny