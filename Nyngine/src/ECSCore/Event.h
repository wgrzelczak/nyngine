#pragma once
#include "Preinclude.h"
#include "EventListener.h"

namespace ny::ECS::Core
{
    class EventBase
    {
    };

    template <class T, class D>
    class Event : public EventBase
    {
    public:
        using Data = D;
        using Function = void (*)(const Data&);
        using Listener = EventListener<D>*;

        const static u32 Id;

        Event()
        {
            NY_TRACE("Event constructed id: ", Id);
        }

        static void RegisterListener(Listener listener);
        static void InvokeAll(const Data& data);

    private:
        void Register(Listener listener);
        void Invoke(const Data& data);

        std::vector<Listener> m_listeners;
    };

    static u32 EVENT_NEXT_ID{0};
    template <class T, class Data>
    const u32 Event<T, Data>::Id = EVENT_NEXT_ID++;

    template <class T, class D>
    inline void Event<T, D>::RegisterListener(Listener listener)
    {
        if (auto ptr = std::static_pointer_cast<Event<T, D>>(ECS::Get()->GetEventManager()->GetEvent<T>(Id).lock()))
        {
            ptr->Register(listener);
        }
    }

    template <class T, class D>
    inline void Event<T, D>::InvokeAll(const Data& data)
    {
        if (auto ptr = std::static_pointer_cast<Event<T, D>>(ECS::Get()->GetEventManager()->GetEvent<T>(Id).lock()))
        {
            ptr->Invoke(data);
        }
    }

    template <class T, class D>
    inline void Event<T, D>::Register(Listener listener)
    {
        m_listeners.push_back(listener);
    }

    template <class T, class D>
    inline void Event<T, D>::Invoke(const Data& data)
    {
        std::for_each(std::begin(m_listeners), std::end(m_listeners), [data](Listener listener) {
            (*listener)(data);
        });
    }
} // namespace ny::ECS::Core