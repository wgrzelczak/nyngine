
template <class T>
inline std::weak_ptr<T> ComponentManager::GetEntityComponent(const id::Entity& entity)
{
    _LOG_FUNC();
    const id::Component component = Component<T>::GetId();

    {
        auto it = mComponents.find(component);
        if (it != std::end(mComponents))
        {
            auto container = std::static_pointer_cast<core::ComponentContainer<T>>(it->second);
            return container->GetComponent(entity);
        }
    }

    return std::weak_ptr<T>();
}

template <class T>
inline std::weak_ptr<T> ComponentManager::AddEntityComponent(const id::Entity& id)
{
    _LOG_FUNC();
    const id::Component componentId = Component<T>::GetId();

    {
        auto container = std::static_pointer_cast<core::ComponentContainer<T>>(mComponents[componentId]);
        if (container == nullptr)
        {
            container.reset(new core::ComponentContainer<T>());
            mComponents[componentId] = container;
        }
        return container->AddComponent(id);
    }

    return std::weak_ptr<T>();
}