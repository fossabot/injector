#include "injector/errors.hpp"

namespace injector
{
    const char* ComponentCreationException::what() const noexcept
    {
        return "Failed to create component";
    }

} // namespace injector