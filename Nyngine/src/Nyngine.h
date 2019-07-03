#pragma once
#include "Core/Engine.h"

namespace ny
{
    template <class A>
    i32 Run()
    {
        static_assert(std::is_base_of<ny::Core::Application, A>(), "A should derive from ny::Core::Aplication: " __FUNCSIG__);

        return ny::Core::Engine::GetInstance()->Run(new A());
    }
} // namespace ny