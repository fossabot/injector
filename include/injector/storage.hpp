#pragma once

#include <memory>

#include "factory.hpp"

namespace injector
{
    class Injector;

    template<class T>
    class InstanceStorage
    {
    public:
        explicit InstanceStorage(std::unique_ptr<ComponentFactory<T>>&& factory)
            : m_Factory(std::move(factory))
        {
        }

        virtual std::shared_ptr<T> get(Injector& injector)
        {
            return m_Factory->build(injector);
        }

    private:
        std::unique_ptr<ComponentFactory<T>> m_Factory;
    };

    template<class T>
    class SingletonInstanceStorage : public InstanceStorage<T>
    {
        using base = InstanceStorage<T>;

    public:
        explicit SingletonInstanceStorage(std::unique_ptr<ComponentFactory<T>>&& factory)
            : base(std::move(factory))
        {
        }

        std::shared_ptr<T> get(Injector& injector) override
        {
            if (!m_Instance)
            {
                m_Instance = base::get(injector);
            }

            return m_Instance;
        }

    private:
        std::shared_ptr<T> m_Instance;
    };
} // namespace injector