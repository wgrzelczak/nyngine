#pragma once
#include "Preinclude.h"
#include "Entity.h"

namespace ny::ECS::Core
{
    class SystemBase
    {
    public:
        virtual void Update() = 0;
        virtual void RegisterEntity(Entity* const entity) = 0;
    };

    template <class RequiredComponent>
    class System : public SystemBase
    {
    public:
        virtual void Update() final;
        virtual void RegisterEntity(Entity* const entity) final;

    protected:
        using pFuncUpdate = void (*)(const std::shared_ptr<RequiredComponent>&);
        pFuncUpdate m_updateCallback = nullptr;

        std::list<std::shared_ptr<RequiredComponent>> m_components;
    };

    template <class RequiredComponent>
    inline void System<RequiredComponent>::Update()
    {
        std::for_each(std::begin(m_components), std::end(m_components), m_updateCallback);
    }

    template <class RequiredComponent>
    inline void System<RequiredComponent>::RegisterEntity(Entity* const entity)
    {
        if (auto ptr = entity->GetComponent<RequiredComponent>())
        {
            m_components.push_back(ptr);
        }
        else
        {
            NY_WARN("[ECS] Entity {} has NOT requred component!", entity->GetId());

            ptr = entity->AddComponent<RequiredComponent>();
            m_components.push_back(ptr);
        }
    }
} // namespace ny::ECS::Core