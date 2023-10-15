#include <smal/Memory/Part.hpp>

namespace smal
{
    Part::Part()
        : m_origin {0}
        , m_memory {0}
        , m_length {0}
    { }

    Part::Part(BaseOrigin* origin, void* memory, usize length)
        : m_origin {origin}
        , m_memory {(char*) memory}
        , m_length {length}
    { }

    bool
    Part::isNull() const
    {
        return this->m_memory == 0;
    }

    const BaseOrigin*
    Part::origin() const
    {
        return this->m_origin;
    }

    char*
    Part::memory()
    {
        return this->m_memory;
    }

    const char*
    Part::memory() const
    {
        return this->m_memory;
    }

    usize
    Part::length() const
    {
        return this->m_length;
    }
} // namespace smal
