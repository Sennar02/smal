#include <smal/Memory/Part.hpp>

namespace smal
{
    Part::Part()
        : m_origin {0}
        , m_memory {0}
        , m_length {0}
    { }

    Part::Part(void* origin, void* memory, usize length)
        : m_origin {origin}
        , m_memory {memory}
        , m_length {length}
    { }

    bool
    Part::isNull() const
    {
        return this->m_memory == 0 ||
               this->m_length == 0 ||
               this->m_origin == 0;
    }

    usize
    Part::length() const
    {
        return this->m_length;
    }

    void*
    Part::origin() const
    {
        return this->m_origin;
    }

    char*
    Part::memory() const
    {
        return (char*) this->m_memory;
    }
} // namespace smal
