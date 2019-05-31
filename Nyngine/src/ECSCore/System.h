#pragma once
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
        void Update();
        void RegisterEntity(Entity* const entity);

    protected:
        using pFuncUpdate = void (*)(const std::shared_ptr<RequiredComponent>&);
        pFuncUpdate UpdateComponent;

        std::list<std::shared_ptr<RequiredComponent>> m_components;
    };

    template <class RequiredComponent>
    inline void System<RequiredComponent>::Update()
    {
        std::for_each(std::begin(m_components), std::end(m_components), UpdateComponent);
    }

    template <class RequiredComponent>
    inline void System<RequiredComponent>::RegisterEntity(Entity* const entity)
    {
        if (auto weak = entity->GetComponent<RequiredComponent>(); !weak.lock())
        {
            //_ASSERT(false);
            weak = entity->AddComponent<RequiredComponent>();
            m_components.push_back(weak);
        }
        else
        {
            m_components.push_back(weak);
        }
    }
} // namespace ny::ECS::Core