#include <smal/Memory/Block/PageTable.hpp>

namespace ma
{
    PageTable::PageTable()
        : m_memory {0}
        , m_size {1}
        , m_page {1}
        , m_count {0}
    { }

    PageTable::PageTable(void* memory, u32 size, u32 page)
        : m_memory {0}
        , m_size {1}
        , m_page {1}
        , m_count {0}
    {
        if ( m_page != 0 ) {
            m_memory = (Node*) memory;

            m_size = size / s_node_size;
            m_page = page;
        }
    }

    u32
    PageTable::size() const
    {
        return m_size;
    }

    u32
    PageTable::count() const
    {
        return m_count;
    }

    u32
    PageTable::page() const
    {
        return m_page;
    }

    bool
    PageTable::isEmpty() const
    {
        return m_count == 0;
    }

    bool
    PageTable::isFull() const
    {
        return m_count == m_size;
    }

    bool
    PageTable::push(void* memory)
    {
        u32 count = m_count;

        if ( m_count < m_size )
            m_memory[m_count++] = (char*) memory;

        return m_count != count;
    }

    char*
    PageTable::pull()
    {
        char* addr = 0;

        if ( m_count > 0 )
            swap(m_memory[--m_count], addr);

        return addr;
    }

    char*
    PageTable::find(u32 index) const
    {
        if ( m_size > index )
            return m_memory[index];

        return 0;
    }

    char*
    PageTable::convert(u32 index, u32 size) const
    {
        u32 byte = index * size;

        return m_memory[byte / m_page] +
               (byte % m_page);
    }
} // namespace ma
