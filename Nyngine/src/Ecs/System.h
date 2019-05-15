#pragma once
#include "SystemBase.h"
#include "ecs.h"
#include <algorithm>
#include <functional>
#include <list>
#include <memory>
#include <tuple>
namespace engine::ecs
{
    template <class RequiredComponent, Priority P = Priority::UNDEFINED>
    class System : public core::SystemBase
    {
    public:
        void Update() override;

        void RegisterEntity(core::Entity* const entity) override;

    protected:
        System();

        //todo change to std::function (?)
        using pFuncUpdate = void (*)(const std::weak_ptr<RequiredComponent>&);
        pFuncUpdate UpdateComponent;

        std::list<std::weak_ptr<RequiredComponent>> mComponents;
    };
#include "System.inl"
} // namespace engine::ecs