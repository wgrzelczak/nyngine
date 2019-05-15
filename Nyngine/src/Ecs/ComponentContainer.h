#pragma once
#include "Component.h"
#include "ComponentContainerBase.h"
#include "Preinclude.h"
#include <algorithm>
#include <memory>
#include <vector>

namespace engine::ecs::core
{
    template <class T>
    class ComponentContainer : public ComponentContainerBase
    {
    public:
        std::weak_ptr<T> GetComponent(const id::Entity& id);
        std::weak_ptr<T> AddComponent(const id::Entity& id);

    private:
        using Pair = std::pair<id::Entity, std::shared_ptr<T>>;
        std::vector<Pair> mComponents;
    };

#include "ComponentContainer.inl"
} // namespace engine::ecs::core