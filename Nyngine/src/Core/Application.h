#pragma once
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

        virtual Window& GetWindow() const = 0;
    };

    template <class LayerV>
    class ApplicationExt : public Application
    {
      protected:
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

        template <class EventType>
        void OnEvent(EventType&& event)
        {
            auto dispatchEvent = [&](auto&& arg) {
                using LayerType = std::decay_t<decltype(arg)>;
                if constexpr (HasEvent<LayerType, EventType>)
                {
                    arg.OnEvent(std::forward<EventType>(e));
                }
            };

            for (auto& l : m_layers)
            {
                if (!e.m_handled)
                {
                    std::visit(dispatchEvent, *l);
                }
            }
        }

        std::vector<std::unique_ptr<LayersVariant>> m_layers;
    };
} // namespace ny::Core
