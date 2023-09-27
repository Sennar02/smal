#include <smal/Memory/Page.hpp>

namespace smal
{
    Page::Page()
        : m_origin {0}
        , m_memory {0}
        , m_length {0}
    { }

    Page::Page(PageAlloc* origin, void* memory, long length)
        : m_origin {origin}
        , m_memory {memory}
        , m_length {length}
    { }

    bool
    Page::is_null() const
    {
        return this->m_memory == 0 ||
               this->m_length == 0 ||
               this->m_origin == 0;
    }

    long
    Page::get_length() const
    {
        return this->m_length;
    }

    PageAlloc*
    Page::get_origin() const
    {
        return this->m_origin;
    }

    char*
    Page::get_memory() const
    {
        return (char*) this->m_memory;
    }

    char*
    Page::get_finish() const
    {
        return (char*) this->m_memory +
               this->m_length;
    }
} // namespace smal
