#pragma once
#include "Event/Event.h"
#include "FieldDetection.h"
#include "Layer.h"
#include "Window.h"
#include <variant>

namespace ny::Core
{
    class Application abstract
    {
      public:
        virtual void PreInit() = 0;
        virtual void Init() = 0;
        virtual void LateInit() = 0;
        virtual void Tick() = 0;
        virtual void Shutdown() = 0;
        virtual void OnEvent(Event&) = 0;
        virtual Window& GetWindow() const = 0;

        virtual void ToggleDebugLayer() = 0;
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
                {
                    if (!arg.IsEnabled())
                    {
                        arg.OnEnable();
                        arg.SetIsEnabled(true);
                    }
                }
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
                {
                    if (arg.IsEnabled())
                    {
                        arg.OnDisable();
                        arg.SetIsEnabled(false);
                    }
                }
            };

            for (auto& l : m_layers)
            {
                std::visit(DisableLayer, *l);
            }
        }

        template <class T>
        Layer* GetLayerData()
        {
            Layer* ret = nullptr;
            auto GetLayerData = [&](auto&& arg) {
                using LayerType = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, LayerType>)
                {
                    ret = &arg;
                }
            };
            for (auto& l : m_layers)
            {
                std::visit(GetLayerData, *l);
            }
            return ret;
        }

      protected:
        virtual void PreInit() override final
        {
        }

        virtual void LateInit() override final
        {
            EnableLayer<EngineLayer>();
        }

        using LayersVariant = LayerV;
        void UpdateLayers()
        {
            auto EarlyUpdateLayer = [&](auto&& arg) {
                using LayerType = std::decay_t<decltype(arg)>;
                if constexpr (HasEarlyUpdate<LayerType>)
                {
                    if (arg.IsEnabled())
                        arg.OnEarlyUpdate();
                }
            };

            auto UpdateLayer = [&](auto&& arg) {
                using LayerType = std::decay_t<decltype(arg)>;
                if constexpr (HasUpdate<LayerType>)
                {
                    if (arg.IsEnabled())
                        arg.OnUpdate();
                }
            };

            auto LateUpdateLayer = [&](auto&& arg) {
                using LayerType = std::decay_t<decltype(arg)>;
                if constexpr (HasLateUpdate<LayerType>)
                {
                    if (arg.IsEnabled())
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
                if (!arg.IsEnabled()) return;

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

      private:
        virtual void ToggleDebugLayer() override
        {
            Layer* layerData = GetLayerData<ImGuiLayer>();
            if (!layerData->IsEnabled())
            {
                EnableLayer<ImGuiLayer>();
            }
            else
            {
                DisableLayer<ImGuiLayer>();
            }
        }
    };
} // namespace ny::Core
