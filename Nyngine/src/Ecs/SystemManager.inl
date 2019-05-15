template <class T>
inline std::weak_ptr<T> SystemManager::CreateSystem()
{
    static_assert(std::is_base_of<core::SystemBase, T>(), "Template param should derive from System: " __FUNCSIG__);
    //todo custom alloc
    std::shared_ptr<T> sys(new T());
    RegisterSystem(sys);
    return sys;
}