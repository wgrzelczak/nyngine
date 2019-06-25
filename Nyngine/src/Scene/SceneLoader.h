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
        SceneLoader(const std::string& filename);
        ~SceneLoader();

        void LoadSceneNodes(Scene* scene) {}
        EcsEntity* CreateEntityByNodeIndex(i32 nodeId, bool withChildren = false);

    private:
        void LoadTransform(fx::gltf::Node& node, ECS::Transform& transform);
        Rendering::Mesh* LoadMesh(fx::gltf::Mesh& inMesh);

        void GetAccessorData(i32 accessorId, Rendering::Mesh::VertexAttributesSettings::Data& data);

        fx::gltf::Document m_doc;
    };
} // namespace ny