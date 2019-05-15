#pragma once
#include "Event.h"
#include "Preinclude.h"
#include <map>
namespace ny::Ecs
{
    class EventManager
    {
    public:
        template <class E>
        std::shared_ptr<E> GetEvent(const u32 id);

    private:
        std::map<u32, std::shared_ptr<EventBase>> m_events;
    };

    template <class E>
    inline std::shared_ptr<E> EventManager::GetEvent(const u32 id)
    {
        auto ptr = m_events.find(id);
        if (ptr != std::end(m_events))
            return nullptr;

        return ptr;
    }

} // namespace ny::Ecs