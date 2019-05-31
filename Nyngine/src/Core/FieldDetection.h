#pragma once

// NOTE: Fields are detected only if they are public

namespace ny::Core
{
    namespace Helpers
    {
        template <class L>
        constexpr decltype(std::declval<L>().OnUpdate(), true) has_update() { return true; }

        template <class L>
        constexpr bool has_update(...) { return false; }

        template <class L, class E>
        constexpr decltype(std::declval<L>().OnEvent(std::declval<E>()), true) has_event() { return true; }

        template <class L, class E>
        constexpr bool has_event(...) { return false; }
    } // namespace Helpers

    template <class L>
    constexpr bool HasUpdate = Helpers::has_update<L>();

    template <class L, class E>
    constexpr bool HasEvent = Helpers::has_event<L, E>();
} // namespace ny::Core
