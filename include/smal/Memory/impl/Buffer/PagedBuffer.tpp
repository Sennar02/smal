#include <smal/Memory/Buffer/PagedBuffer.hpp>

namespace ma
{
    namespace impl
    {
        static PoolOrigin s_null;
    } // namespace impl

    template <class Item>
    const u32 PagedBuffer<Item>::s_item_size =
        sizeof(Item);

    template <class Item>
    PagedBuffer<Item>::PagedBuffer()
        : m_memory {}
        , m_origin {&impl::s_null}
        , m_page {s_item_size}
    { }

    template <class Item>
    PagedBuffer<Item>::PagedBuffer(PoolOrigin& origin, u32 size)
        : PagedBuffer()
    {
        char* addr = origin.acquire();

        if ( addr != 0 ) {
            m_page   = origin.page();
            m_memory = {addr, m_page};
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
    template <class Origin>
    PagedBuffer<Item>::PagedBuffer(Origin& origin, u32 size, u32 page)
        : PagedBuffer()
    {
        char* addr = 0;

        if ( page >= s_item_size ) {
            addr = origin.acquire(page);

            m_page   = page;
            m_memory = {addr, m_page};
            m_origin = &origin;

            resize(size);
        }
    }

    template <class Item>
    template <class Origin>
    PagedBuffer<Item>::PagedBuffer(Origin& origin, u32 size, u32 page, const Item& item)
        : PagedBuffer(origin, size, page)
    {
        size = m_memory.size();

        for ( u32 i = 0; i < size; i++ )
            find(i) = item;
    }

    template <class Item>
    PagedBuffer<Item>::PagedBuffer(MemoryTable&& memory, u32 page, BaseOrigin* origin)
        : PagedBuffer()
    {
        if ( page >= s_item_size ) {
            m_memory = memory;
            m_origin = origin;
            m_page   = page;
        }
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

        if ( size - m_memory.count() >= pages ) {
            for ( u32 i = 0; i < pages; i++ ) {
                addr = m_origin->acquire(m_page);

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

        if ( m_memory.count() >= pages ) {
            for ( u32 i = 0; i < pages; i++ ) {
                addr = m_memory.remove();

                if ( addr != 0 ) {
                    if ( m_origin->release(addr) == false )
                        return false;
                } else
                    return false;
            }
        }

        return true;
    }

    template <class Item>
    Item*
    PagedBuffer<Item>::search(u32 index) const
    {
        u32 page = m_page;
        u32 byte = s_item_size * index;

        return (Item*) m_memory.convert(byte, page);
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
        u32 size = m_page / s_item_size;

        return pages * size;
    }

    template <class Item>
    u32
    PagedBuffer<Item>::toPages(u32 items) const
    {
        u32 size = m_page / s_item_size;

        if ( items % size == 0 )
            return items / size;

        return items / size + 1u;
    }
} // namespace ma
