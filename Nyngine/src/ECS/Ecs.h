#pragma once
#include "ECSCore/EcsManager.h"
#include "GameEntity.h"

using Ecs = ny::ECS::Core::EcsManager;

using EcsCoreEntity = ny::ECS::Core::Entity;
using EcsEntity = ny::ECS::GameEntity;

template <class T>
using EcsComponent = ny::ECS::Core::Component<T>;

template <class T>
using EcsSystem = ny::ECS::Core::System<T>;

template <class T, class D>
using EcsEvent = ny::ECS::Core::Event<T, D>;