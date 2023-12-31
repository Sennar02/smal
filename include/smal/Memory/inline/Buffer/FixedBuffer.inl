#include <smal/Memory/Buffer/FixedBuffer.hpp>

namespace ma
{
    template <class Item>
    const u32 FixedBuffer<Item>::s_item_size =
        sizeof(Item);

    template <class Item>
    FixedBuffer<Item>::FixedBuffer(u32 size)
        : FixedBuffer(g_origin, size)
    { }

    template <class Item>
    template <class Type>
    FixedBuffer<Item>::FixedBuffer(Type memory[], u32 size)
        : m_memory {0}
        , m_size {0}
    {
        char* addr = (char*) memory;

        if ( memory != 0 && size != 0 ) {
            m_memory = addr;
            m_size   = size;
        }
    }

    template <class Item>
    FixedBuffer<Item>::FixedBuffer(BaseOrigin& origin, u32 size, const Item& item)
        : FixedBuffer(origin, size)
    {
        for ( u32 i = 0; i < m_size; i++ )
            find(i) = item;
    }

    template <class Item>
    FixedBuffer<Item>::FixedBuffer(BaseOrigin& origin, u32 size)
        : FixedBuffer(origin.acquire(size * s_item_size), size)
    { }

    template <class Item>
    Item*
    FixedBuffer<Item>::memory() const
    {
        return (Item*) m_memory;
    }

    template <class Item>
    u32
    FixedBuffer<Item>::size() const
    {
        return m_size;
    }

    template <class Item>
    bool
    FixedBuffer<Item>::resize(u32 size)
    {
        return m_size == size;
    }

    template <class Item>
    Item&
    FixedBuffer<Item>::find(u32 index) const
    {
        return *((Item*) m_memory + index);
    }

    template <class Item>
    Item&
    FixedBuffer<Item>::operator[](u32 index) const
    {
        return find(index);
    }
} // namespace ma
