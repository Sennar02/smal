#include <smal/Memory/Buffer/PagedBuffer.hpp>

namespace ma
{
    template <class Item>
    const u32 PagedBuffer<Item>::s_item_size =
        sizeof(Item);

    template <class Item>
    PagedBuffer<Item>::PagedBuffer()
        : m_memory {}
        , m_origin {0}
    { }

    template <class Item>
    PagedBuffer<Item>::PagedBuffer(PoolOrigin& origin, u32 size)
        : PagedBuffer()
    {
        char* addr = origin.acquire();
        u32   page = origin.page();

        if ( addr != 0 ) {
            m_memory = {addr, page};
            m_origin = &origin;

            resize(size);
        }
    }

    template <class Item>
    PagedBuffer<Item>::PagedBuffer(PoolOrigin& origin, u32 size, const Item& item)
        : PagedBuffer(origin, size)
    {
        size = m_memory.size();

        for ( u32 i = 0; i < size; i++ )
            find(i) = item;
    }

    template <class Item>
    PagedBuffer<Item>::PagedBuffer(MemoryTable&& memory, PoolOrigin* origin)
        : PagedBuffer()
    {
        m_memory = move(memory);
        m_origin = origin;
    }

    template <class Item>
    const MemoryTable&
    PagedBuffer<Item>::memory() const
    {
        return m_memory;
    }

    template <class Item>
    u32
    PagedBuffer<Item>::size() const
    {
        return toItems(m_memory.count());
    }

    template <class Item>
    bool
    PagedBuffer<Item>::resize(u32 size)
    {
        u32 count = m_memory.count();
        u32 pages = toPages(size);

        if ( count != pages ) {
            if ( count < pages )
                return expand(pages - count);

            return shrink(count - pages);
        }

        return true;
    }

    template <class Item>
    bool
    PagedBuffer<Item>::expand(u32 pages)
    {
        char* addr = 0;
        u32   size = m_memory.size();

        if ( m_origin->count() < pages ) return false;

        if ( size - m_memory.count() >= pages ) {
            for ( u32 i = 0; i < pages; i++ ) {
                addr = m_origin->acquire();

                if ( m_memory.insert(addr) == false )
                    return false;
            }
        }

        return true;
    }

    template <class Item>
    bool
    PagedBuffer<Item>::shrink(u32 pages)
    {
        char* addr = 0;

        if ( m_memory.count() < pages ) return false;

        for ( u32 i = 0; i < pages; i++ ) {
            addr = m_memory.remove();

            if ( addr == 0 || m_origin->release(addr) == false )
                return false;
        }

        return true;
    }

    template <class Item>
    Item*
    PagedBuffer<Item>::search(u32 index) const
    {
        u32 byte = index * s_item_size;
        u32 page = byte / m_origin->page();
        u32 dist = byte % m_origin->page();

        return (Item*) m_memory.find(page, dist);
    }

    template <class Item>
    Item&
    PagedBuffer<Item>::find(u32 index) const
    {
        return *search(index);
    }

    template <class Item>
    Item&
    PagedBuffer<Item>::operator[](u32 index) const
    {
        return *search(index);
    }

    template <class Item>
    u32
    PagedBuffer<Item>::toItems(u32 pages) const
    {
        u32 page = m_origin->page();
        u32 size = page / s_item_size;

        return pages * size;
    }

    template <class Item>
    u32
    PagedBuffer<Item>::toPages(u32 items) const
    {
        u32 page = m_origin->page();
        u32 size = page / s_item_size;

        if ( items % size == 0 )
            return items / size;

        return items / size + 1u;
    }
} // namespace ma
