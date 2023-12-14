#include <smal/Memory/Buffer/SimpleBuffer.hpp>

namespace ma
{
    template <class Item>
    const u32 SimpleBuffer<Item>::s_item_size =
        sizeof(Item);

    template <class Item>
    SimpleBuffer<Item>::SimpleBuffer()
        : m_memory {0}
        , m_size {0}
    { }

    template <class Item>
    template <class Type>
    SimpleBuffer<Item>::SimpleBuffer(Type memory[], u32 size)
        : SimpleBuffer()
    {
        char* addr = (char*) memory;

        if ( memory != 0 && size != 0 ) {
            m_memory = addr;
            m_size   = size;
        }
    }

    template <class Item>
    template <class Origin>
    SimpleBuffer<Item>::SimpleBuffer(Origin& origin, u32 size)
        : SimpleBuffer(origin.acquire(size * s_item_size), size)
    { }

    template <class Item>
    template <class Origin>
    SimpleBuffer<Item>::SimpleBuffer(Origin& origin, u32 size, const Item& item)
        : SimpleBuffer(origin, size)
    {
        for ( u32 i = 0; i < m_size; i++ )
            find(i) = item;
    }

    template <class Item>
    Item*
    SimpleBuffer<Item>::memory() const
    {
        return (Item*) m_memory;
    }

    template <class Item>
    u32
    SimpleBuffer<Item>::size() const
    {
        return m_size;
    }

    template <class Item>
    bool
    SimpleBuffer<Item>::resize(u32 size)
    {
        return m_size == size;
    }

    template <class Item>
    Item&
    SimpleBuffer<Item>::find(u32 index) const
    {
        return ((Item*) m_memory)[index];
    }

    template <class Item>
    Item&
    SimpleBuffer<Item>::operator[](u32 index) const
    {
        return ((Item*) m_memory)[index];
    }
} // namespace ma
