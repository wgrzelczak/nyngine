#pragma once
#include "Event/Event.h"
#include "FieldDetection.h"
#include "Window.h"
#include <variant>

namespace ny::Core
{
    class Application abstract
    {
      public:
        virtual void PreInit() = 0;
        virtual void Init() = 0;
        virtual void Tick() = 0;
        virtual void Shutdown() = 0;
        virtual void OnEvent(Event&) = 0;
        virtual Window& GetWindow() const = 0;
    };

    template <class LayerV>
    class ApplicationExt : public Application
    {
      public:
        template <class T>
        void EnableLayer()
        {
            auto EnableLayer = [&](auto&& arg) {
                using LayerType = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, LayerType> && HasEnable<T>)
                    arg.OnEnable();
            };

            for (auto& l : m_layers)
            {
                std::visit(EnableLayer, *l);
            }
        }

        template <class T>
        void DisableLayer()
        {
            auto DisableLayer = [&](auto&& arg) {
                using LayerType = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, LayerType> && HasDisable<T>)
                    arg.OnDisable();
            };

            for (auto& l : m_layers)
            {
                std::visit(DisableLayer, *l);
            }
        }

      protected:
        virtual void PreInit() override
        {
        }

        using LayersVariant = LayerV;

        void UpdateLayers()
        {
            auto EarlyUpdateLayer = [&](auto&& arg) {
                using LayerType = std::decay_t<decltype(arg)>;
                if constexpr (HasEarlyUpdate<LayerType>)
                {
                    arg.OnEarlyUpdate();
                }
            };

            auto UpdateLayer = [&](auto&& arg) {
                using LayerType = std::decay_t<decltype(arg)>;
                if constexpr (HasUpdate<LayerType>)
                {
                    arg.OnUpdate();
                }
            };

            auto LateUpdateLayer = [&](auto&& arg) {
                using LayerType = std::decay_t<decltype(arg)>;
                if constexpr (HasLateUpdate<LayerType>)
                {
                    arg.OnLateUpdate();
                }
            };

            for (auto& l : m_layers)
            {
                std::visit(EarlyUpdateLayer, *l);
            }

            for (auto& l : m_layers)
            {
                std::visit(UpdateLayer, *l);
            }

            for (auto& l : m_layers)
            {
                std::visit(LateUpdateLayer, *l);
            }
        }

        void OnEvent(Event& e)
        {
            auto DispatchEvent = [&](auto&& arg) {
                EVENT_DISPATCH(arg, e, WindowClosedEvent);
                EVENT_DISPATCH(arg, e, WindowResizedEvent);
                EVENT_DISPATCH(arg, e, KeyPressedEvent);
                EVENT_DISPATCH(arg, e, KeyReleasedEvent);
                EVENT_DISPATCH(arg, e, KeyTypedEvent);
                EVENT_DISPATCH(arg, e, MouseButtonPressedEvent);
                EVENT_DISPATCH(arg, e, MouseButtonReleasedEvent);
                EVENT_DISPATCH(arg, e, MouseScrolledEvent);
                EVENT_DISPATCH(arg, e, MouseMovedEvent);
            };

            for (auto& l : m_layers)
            {
                if (e.m_handled)
                    break;

                std::visit(DispatchEvent, *l);
            }
        }

        template <class T>
        void PushLayer()
        {
            m_layers.push_back(std::make_unique<LayersVariant>(std::in_place_type_t<T>()));
        }

        std::vector<std::unique_ptr<LayersVariant>> m_layers;
    };
} // namespace ny::Core
