#pragma once
#include "ECS/Ecs.h"
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
        void LoadMesh(fx::gltf::Mesh& inMesh, EcsEntity* entity);

        void GetAccessorData(i32 accessorId, u8& elementSize, u32& elementsNum, void*& data);

        fx::gltf::Document m_doc;
    };
} // namespace ny