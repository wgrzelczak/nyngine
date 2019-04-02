#pragma once
#include "pch.h"
#include "Components\Component.h"
#include "Preinclude.h"

namespace ny
{
    class Entity
    {
      public:
        Entity();
        ~Entity();

        void Destroy();

        u32 m_id;
        std::vector<std::shared_ptr<Component>> m_components;

        static u32 lastId;
    };
} // namespace ny