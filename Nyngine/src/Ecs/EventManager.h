#pragma once
#include "EventBase.h"
#include "Preinclude.h"
#include <map>
#include <memory>
namespace engine::ecs
{
    class EventManager
    {
    public:
        EventManager() {}
        ~EventManager() {}

        template <class E>
        std::weak_ptr<E> GetEvent(const id::Event& ID);

    private:
        std::map<id::Event, std::shared_ptr<core::EventBase>> mEvents;
    };

#include "EventManager.inl"
} // namespace engine::ecs