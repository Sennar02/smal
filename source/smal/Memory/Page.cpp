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
        return this->m_origin == 0 ||
               this->m_memory == 0 ||
               this->m_size == 0;
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
    Page::size() const
    {
        return this->m_size;
    }
} // namespace ma
