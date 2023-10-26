#include <smal/Memory/Page.hpp>

namespace ma
{
    Page::Page()
        : m_origin {0}
        , m_memory {0}
        , m_length {0}
    { }

    Page::Page(BaseOrigin* origin, void* memory, usize length)
        : m_origin {origin}
        , m_memory {(char*) memory}
        , m_length {length}
    { }

    bool
    Page::isNull() const
    {
        return this->m_memory == 0;
    }

    const BaseOrigin*
    Page::origin() const
    {
        return this->m_origin;
    }

    char*
    Page::memory()
    {
        return this->m_memory;
    }

    const char*
    Page::memory() const
    {
        return this->m_memory;
    }

    usize
    Page::length() const
    {
        return this->m_length;
    }
} // namespace ma
