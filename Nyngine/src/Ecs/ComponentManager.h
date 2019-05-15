#pragma once
#include "Component.h"
#include "ComponentContainer.h"
#include "Entity.h"
#include "Preinclude.h"
#include <map>
#include <vector>

namespace engine::ecs
{
    using namespace core;
    class ComponentManager
    {
    public:
        ComponentManager(){};
        ~ComponentManager(){};

    private:
        friend class Entity;
        friend class ComponentBase;

        template <class T>
        std::weak_ptr<T> GetEntityComponent(const id::Entity& id);

        template <class T>
        std::weak_ptr<T> AddEntityComponent(const id::Entity& id);

        std::map<id::Component, std::shared_ptr<core::ComponentContainerBase>> mComponents;
    };

#include "ComponentManager.inl"
} // namespace engine::ecs