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

    using SystemTypeId = u32;

    template <class T>
    class SystemType : public SystemBase
    {
    public:
        static SystemTypeId GetId() { return Id; }

    protected:
        const static SystemTypeId Id;
    };

    static SystemTypeId NEXT_SYSTEM_ID{0};
    template <class T>
    const SystemTypeId SystemType<T>::Id = NEXT_SYSTEM_ID++;

    template <class T, class C>
    class System : public SystemType<C>
    {
    public:
        virtual void Update() final;
        virtual void RegisterEntity(Entity* const entity) final;

    protected:
        std::list<std::shared_ptr<C>> m_components;

        using pFuncUpdate = void (*)(const std::shared_ptr<C>&);
        pFuncUpdate m_updateCallback{nullptr};
    };

    template <class T, class C>
    inline void System<T, C>::Update()
    {
        std::for_each(std::begin(m_components), std::end(m_components), m_updateCallback);
    }

    template <class T, class C>
    inline void System<T, C>::RegisterEntity(Entity* const entity)
    {
        if (auto ptr = entity->GetComponent<C>())
        {
            m_components.push_back(ptr);
        }
        else
        {
            NY_WARN("[ECS] Entity {} has NOT requred component!", entity->GetId());

            ptr = entity->AddComponent<C>();
            m_components.push_back(ptr);
        }
    }
} // namespace ny::ECS::Core