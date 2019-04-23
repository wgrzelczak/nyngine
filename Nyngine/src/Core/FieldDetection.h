#pragma once

// NOTE: Fields are detected only if they are public

namespace ny::Core
{
    namespace Helpers
    {
        template <class L>
        constexpr decltype(std::declval<L>().OnEarlyUpdate(), true) has_early_update() { return true; }

        template <class L>
        constexpr bool has_early_update(...) { return false; }

        template <class L>
        constexpr decltype(std::declval<L>().OnUpdate(), true) has_update() { return true; }

        template <class L>
        constexpr bool has_update(...) { return false; }

        template <class L>
        constexpr decltype(std::declval<L>().OnLateUpdate(), true) has_late_update() { return true; }

        template <class L>
        constexpr bool has_late_update(...) { return false; }

        template <class L, class E>
        constexpr decltype(std::declval<L>().OnEvent(std::declval<E>()), true) has_event() { return true; }

        template <class L, class E>
        constexpr bool has_event(...) { return false; }
    } // namespace Helpers

    template <class L>
    constexpr bool HasEarlyUpdate = Helpers::has_early_update<L>();

    template <class L>
    constexpr bool HasUpdate = Helpers::has_update<L>();

    template <class L>
    constexpr bool HasLateUpdate = Helpers::has_late_update<L>();

    template <class L, class E>
    constexpr bool HasEvent = Helpers::has_event<L, E>();
} // namespace ny::Core
