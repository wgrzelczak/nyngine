#pragma once
#include "Preinclude.h"
#include "Component.h"

namespace ny::ECS::Core
{
    class ComponentContainerBase
    {
    };

    template <class T>
    class ComponentContainer : public ComponentContainerBase
    {
    public:
        std::shared_ptr<T> GetComponent(const Entity* entity);
        std::shared_ptr<T> AddComponent(const Entity* entity);

    private:
        using Pair = std::pair<u32, std::shared_ptr<T>>;
        std::vector<Pair> m_components;
    };

    template <class T>
    std::shared_ptr<T> ComponentContainer<T>::GetComponent(const Entity* entity)
    {
        auto getById = [&entity](const Pair& p) {
            return p.first == entity->GetId();
        };

        auto it = std::find_if(std::begin(m_components), std::end(m_components), getById);
        return it != std::end(m_components) ? it->second : nullptr;
    }

    template <class T>
    inline std::shared_ptr<T> ComponentContainer<T>::AddComponent(const Entity* entity)
    {
        std::shared_ptr<T> component(new T(entity));
        m_components.emplace_back(entity->GetId(), component);
        return component;
    }
} // namespace ny::ECS::Core