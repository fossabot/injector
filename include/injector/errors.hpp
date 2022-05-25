#pragma once

#include <exception>

namespace injector
{
    class InjectorException : public std::exception
    {
    };

    class ComponentCreationException : public InjectorException
    {
    public:
        [[nodiscard]] const char* what() const noexcept override;
    };
} // namespace injector