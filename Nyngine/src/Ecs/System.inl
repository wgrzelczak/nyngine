#include "System.h"

template <class RequiredComponent, Priority P>
inline engine::ecs::System<RequiredComponent, P>::System()
{
    mPriority = P;
    UpdateComponent = [](const std::weak_ptr<RequiredComponent>&) {};
}

template <class RequiredComponent, Priority P>
inline void System<RequiredComponent, P>::Update()
{
    _LOG_FUNC();
    std::for_each(std::begin(mComponents), std::end(mComponents), UpdateComponent);
}

template <class RequiredComponent, Priority P>
inline void engine::ecs::System<RequiredComponent, P>::RegisterEntity(core::Entity* const entity)
{
    _LOG_FUNC();
    if (auto weak = entity->GetComponent<RequiredComponent>(); !weak.lock())
    {
        //_ASSERT(false);
        weak = entity->AddComponent<RequiredComponent>();
        mComponents.push_back(weak);
    }
    else
    {
        mComponents.push_back(weak);
    }
}