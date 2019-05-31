#pragma once

namespace ny::ECS::Core
{
    class ComponentBase
    {
    public:
        ComponentBase() :
            m_enabled(true)
        {}

        bool m_enabled;
    };

    template <class T>
    class Component : public ComponentBase
    {
    public:
        static u32 GetId() { return Id; }

        void SetEntityId(const u32 id) { m_id = id; }
        u32 GetEntityId() const { return m_id; }

    private:
        const static u32 Id;
        u32 m_id;
    };

    static u32 NEXT_COMPONENT_ID = 0;
    template <class T>
    const u32 Component<T>::Id = NEXT_COMPONENT_ID++;
} // namespace ny::ECS::Core