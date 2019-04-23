#pragma once
#include "FieldDetection.h"
#include "Window.h"
#include <variant>
#include "Event/Event.h"

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
      protected:
        virtual void PreInit() override
        {
        }

        using LayersVariant = LayerV;

        void UpdateLayers()
        {
            auto updateLayer = [&](auto&& arg) {
                using LayerType = std::decay_t<decltype(arg)>;
                if constexpr (HasUpdate<LayerType>)
                {
                    arg.OnUpdate();
                }
            };

            for (auto& l : m_layers)
            {
                std::visit(updateLayer, *l);
            }
        }

        template <class T>
        void PushLayer()
        {
            m_layers.push_back(std::make_unique<LayersVariant>(std::in_place_type_t<T>()));
        }

        void OnEvent(Event& e)
        {
            auto dispatchEvent = [&](auto&& arg)
			{
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
                
				std::visit(dispatchEvent, *l);
            }
        }

        std::vector<std::unique_ptr<LayersVariant>> m_layers;
    };
} // namespace ny::Core
