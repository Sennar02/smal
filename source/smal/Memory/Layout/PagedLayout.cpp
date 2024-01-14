#include <smal/Memory/Layout/PagedLayout.hpp>

namespace ma
{
    PagedLayout::PagedLayout(PoolOrigin& origin, u32 items, u32 scale)
        : m_origin {&origin}
        , m_memory {origin.acquire(), origin.page()}
    {
        resize(items, scale);
    }

    u32
    PagedLayout::length(u32 scale) const
    {
        return m_origin->page() / scale * m_memory.count();
    }

    bool
    PagedLayout::resize(u32 items, u32 scale)
    {
        u32 count = m_memory.count();
        // fix: use ceil instead.
        u32 pages = items * scale / m_origin->page();

        if ( (items * scale) % m_origin->page() != 0 )
            pages += 1u;

        if ( pages == count ) return true;

        if ( pages > count )
            return expand(pages - count);

        return shrink(count - pages);
    }

    char&
    PagedLayout::find(u32 index, u32 scale) const
    {
        u32 page = m_origin->page();
        u32 byte = index * scale;

        return *m_memory.convert(byte, page);
    }

    bool
    PagedLayout::expand(u32 pages)
    {
        u32   size = m_memory.length();
        u32   page = m_origin->page();
        void* addr = 0;

        if ( size - m_memory.count() < pages )
            return false;

        for ( u32 i = 0; i < pages; i++ ) {
            addr = m_origin->acquire(page);

            if ( m_memory.insert(addr) == false )
                return false;
        }

        return true;
    }

    bool
    PagedLayout::shrink(u32 pages)
    {
        void* addr = 0;

        if ( m_memory.count() < pages ) return false;

        for ( u32 i = 0; i < pages; i++ ) {
            addr = m_memory.remove();

            if ( m_origin->release(addr) == false )
                return false;
        }

        return true;
    }
} // namespace ma
