#pragma once
#include "EventBase.h"
#include "EventListener.h"
#include "Preinclude.h"
#include "ecs.h"

namespace engine::ecs
{
    template <class T, class D>
    class Event : public core::EventBase
    {
    public:
        using Data = D;
        using Function = void (*)(const Data&);
        using Listener = EventListener<D>*;

        Event()
        {
            std::cout << "Event construct id: " << Id << std::endl;
        }
        const static id::Event Id;

        static void RegisterListener(Listener listener)
        {
            if (auto ptr = std::static_pointer_cast<Event<T, D>>(ECS::Get()->GetEventManager()->GetEvent<T>(Id).lock()))
            {
                ptr->Register(listener);
            }
        }

        static void InvokeAll(const Data& data)
        {
            if (auto ptr = std::static_pointer_cast<Event<T, D>>(ECS::Get()->GetEventManager()->GetEvent<T>(Id).lock()))
            {
                ptr->Invoke(data);
            }
        }

    private:
        std::vector<Listener> mListeners;

        void Register(Listener listener)
        {
            mListeners.push_back(listener);
        }

        void Invoke(const Data& data)
        {
            std::for_each(std::begin(mListeners), std::end(mListeners), [data](Listener listener) {
                (*listener)(data);
            });
        }
    };

    template <class T, class Data>
    const id::Event Event<T, Data>::Id = core::EVENT_NEXT_ID++;
} // namespace engine::ecs