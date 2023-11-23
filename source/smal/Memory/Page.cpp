#include <smal/Memory/Page.hpp>

namespace ma
{
    Page::Page()
        : m_origin {0}
        , m_memory {0}
        , m_size {0}
    { }

    Page::Page(BaseOrigin* origin, void* memory, usize size)
        : m_origin {origin}
        , m_memory {(char*) memory}
        , m_size {size}
    { }

    bool
    Page::is_null() const
    {
        return m_origin == 0 ||
               m_memory == 0 ||
               m_size == 0;
    }

    const BaseOrigin*
    Page::origin() const
    {
        return m_origin;
    }

    char*
    Page::memory()
    {
        return m_memory;
    }

    const char*
    Page::memory() const
    {
        return m_memory;
    }

    usize
    Page::size() const
    {
        return m_size;
    }
} // namespace ma
