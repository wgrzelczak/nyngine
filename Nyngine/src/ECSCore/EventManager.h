#pragma once
#include "Event.h"

namespace ny::ECS::Core
{
    class EcsManager;

    class EventManager
    {
    public:
        EventManager(EcsManager* ecs) :
            p_ecs(ecs)
        {
        }

        template <class E>
        std::shared_ptr<E> GetEvent(const u32 id);

    private:
        EcsManager* p_ecs{nullptr};
        std::map<u32, std::shared_ptr<EventBase>> m_events;
    };

    template <class E>
    inline std::shared_ptr<E> EventManager::GetEvent(const u32 id)
    {
        if (auto ptr = m_events.find(id); ptr == std::end(m_events))
            return ptr;

        return nullptr;
    }

} // namespace ny::ECS::Core