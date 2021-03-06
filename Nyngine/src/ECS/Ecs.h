#pragma once
#include "ECSCore/EcsManager.h"
#include "GameEntity.h"

using Ecs = ny::ECS::Core::EcsManager;
using EcsPtr = std::shared_ptr<Ecs>;

using EcsCoreEntity = ny::ECS::Core::Entity;
using EcsEntity = ny::ECS::GameEntity;

template <class T>
using EcsComponent = ny::ECS::Core::Component<T>;

template <class T, class RequiredComponents>
using EcsSystem = ny::ECS::Core::System<T, RequiredComponents>;

template <class T, class D>
using EcsEvent = ny::ECS::Core::Event<T, D>;