#pragma once
#include "Preinclude.h"
#include "Component.h"
#include "ComponentContainer.h"
#include "Entity.h"

namespace ny::ECS::Core
{
    class EcsManager;

    class ComponentManager
    {
    public:
        ComponentManager()
        {
        }

    private:
        friend class Entity;
        friend class ComponentBase;

        template <class T>
        std::shared_ptr<T> GetEntityComponent(const Entity* entity);

        template <class T>
        std::shared_ptr<T> AddEntityComponent(const Entity* entity);

        std::map<u32, std::shared_ptr<ComponentContainerBase>> m_components;
    };

    template <class T>
    inline std::shared_ptr<T> ComponentManager::GetEntityComponent(const Entity* entity)
    {
        const u32 component = Component<T>::GetId();

        if (auto it = m_components.find(component); it != std::end(m_components))
        {
            auto container = std::static_pointer_cast<ComponentContainer<T>>(it->second);
            return container->GetComponent(entity);
        }

        return nullptr;
    }

    template <class T>
    inline std::shared_ptr<T> ComponentManager::AddEntityComponent(const Entity* entity)
    {
        const u32 componentId = Component<T>::GetId();

        auto container = std::static_pointer_cast<ComponentContainer<T>>(m_components[componentId]);
        if (!container)
        {
            container.reset(new ComponentContainer<T>());
            m_components[componentId] = container;
        }
        return container->AddComponent(entity);
    }
} // namespace ny::ECS::Core