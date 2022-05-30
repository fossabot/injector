#pragma once

#include "storage.hpp"

namespace injector::detail
{
    class IComponentProvider
    {
    public:
        virtual ~IComponentProvider() = default;
    };

    template<class T>
    class ComponentProviderBase : public IComponentProvider
    {
    public:
        virtual std::shared_ptr<T> get(Injector& injector) = 0;
    };

    template<class T>
    class NonCastingComponentProvider : public ComponentProviderBase<T>
    {
    public:
        explicit NonCastingComponentProvider(std::unique_ptr<InstanceStorage<T>>&& storage)
            : m_Storage(std::move(storage))
        {
        }

        std::shared_ptr<T> get(Injector& injector) override
        {
            return m_Storage->get(injector);
        }

    private:
        std::unique_ptr<InstanceStorage<T>> m_Storage;
    };

    template<class Base, class Derived>
    class CastingComponentProvider : public ComponentProviderBase<Base>
    {
    public:
        explicit CastingComponentProvider(std::unique_ptr<InstanceStorage<Derived>>&& storage)
            : m_Storage(std::move(storage))
        {
        }

        std::shared_ptr<Base> get(Injector& injector) override
        {
            return std::static_pointer_cast<Base>(m_Storage->get(injector));
        }

    private:
        std::unique_ptr<InstanceStorage<Derived>> m_Storage;
    };
} // namespace injector::detail