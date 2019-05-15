
template <class T>
std::weak_ptr<T> ComponentContainer<T>::GetComponent(const id::Entity& id)
{
    auto getById = [&id](const Pair& p) {
        return p.first == id;
    };

    auto it = std::find_if(std::begin(mComponents), std::end(mComponents), getById);
    return it != std::end(mComponents) ? it->second : nullptr;
}

template <class T>
inline std::weak_ptr<T> ComponentContainer<T>::AddComponent(const id::Entity& id)
{
    //todo new - add custom allocator + free memory + emplace
    std::shared_ptr<T> component(new T());
    std::static_pointer_cast<Component<T>>(component)->SetEntityId(id);
    mComponents.emplace_back(id, component);
    return component;
}