#pragma once
#include "ComponentBase.h"
#include "ComponentManager.h"

namespace engine::ecs
{
    template <class T>
    class Component : public core::ComponentBase
    {
    public:
        static id::Component GetId() { return mId; }

        void SetEntityId(const id::Entity& id) { mEntityId = id; }
        id::Entity GetEntityId() const { return mEntityId; }

    private:
        const static id::Component mId;
        id::Entity mEntityId;
    };

#include "Component.inl"
} // namespace engine::ecs