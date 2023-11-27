#include <smal/Memory/Block/PageTable.hpp>

namespace ma
{
    PageTable::PageTable()
        : m_memory {0}
        , m_size {1}
        , m_page {1}
        , m_count {0}
    { }

    PageTable::PageTable(void* memory, usize size, usize page)
        : m_memory {0}
        , m_size {1}
        , m_page {1}
        , m_count {0}
    {
        if ( m_page != 0 ) {
            m_memory = (Node*) memory;
            m_size   = size / s_node_size;
            m_page   = page;
        }
    }

    usize
    PageTable::size() const
    {
        return m_size;
    }

    usize
    PageTable::count() const
    {
        return m_count;
    }

    usize
    PageTable::page() const
    {
        return m_page;
    }

    bool
    PageTable::is_empty() const
    {
        return m_count == 0;
    }

    bool
    PageTable::is_full() const
    {
        return m_count == m_size;
    }

    bool
    PageTable::push(void* memory)
    {
        usize count = m_count;

        if ( m_count < m_size )
            m_memory[m_count++] = (char*) memory;

        return m_count != count;
    }

    char*
    PageTable::pull()
    {
        if ( m_count > 0 )
            return m_memory[--m_count];

        return 0;
    }

    char*
    PageTable::find(usize index) const
    {
        if ( m_size > index )
            return m_memory[index];

        return 0;
    }

    char*
    PageTable::convert(usize index, usize size) const
    {
        usize byte = index * size;

        return m_memory[byte / m_page] +
               (byte % m_page);
    }
} // namespace ma
