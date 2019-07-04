#pragma once
#include "Event.h"

namespace ny::ECS::Core
{
    class EcsManager;

    class EventManager
    {
    public:
        EventManager()
        {
        }

        template <class E>
        std::shared_ptr<E> GetEvent(const u32 id);

    private:
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