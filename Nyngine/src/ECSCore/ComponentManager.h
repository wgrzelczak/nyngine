#pragma once
#include "Preinclude.h"
#include "Component.h"
#include "ComponentContainer.h"
#include "Entity.h"

namespace ny::ECS::Core
{
    class ComponentManager
    {
    public:
        ComponentManager(){};
        ~ComponentManager(){};

    private:
        friend class Entity;
        friend class ComponentBase;

        template <class T>
        std::shared_ptr<T> GetEntityComponent(const u32 id);

        template <class T>
        std::shared_ptr<T> AddEntityComponent(const u32 id);

        std::map<u32, std::shared_ptr<ComponentContainerBase>> m_components;
    };

    template <class T>
    inline std::shared_ptr<T> ComponentManager::GetEntityComponent(const u32 entity)
    {
        const u32 component = Component<T>::GetId();

        {
            auto it = m_components.find(component);
            if (it != std::end(m_components))
            {
                auto container = std::static_pointer_cast<ComponentContainer<T>>(it->second);
                return container->GetComponent(entity);
            }
        }

        return nullptr;
    }

    template <class T>
    inline std::shared_ptr<T> ComponentManager::AddEntityComponent(const u32 id)
    {
        const u32 component = Component<T>::GetId();

        {
            auto container = std::static_pointer_cast<ComponentContainer<T>>(m_components[componentId]);
            if (container == nullptr)
            {
                container.reset(new ComponentContainer<T>());
                m_components[componentId] = container;
            }
            return container->AddComponent(id);
        }

        return nullptr;
    }
} // namespace ny::ECS::Core