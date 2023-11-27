#include <smal/Memory/Alloc/PageTable.hpp>

namespace ma
{
    PageTable::PageTable(void* memory, usize size, usize page)
        : m_memory {(Node*) memory}
        , m_size {size / s_node_size}
        , m_page {page}
        , m_count {0}
    {
        if ( m_size == 0 ) m_size = 1;

        if ( m_page == 0 )
            m_page = m_size;
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
    PageTable::insert(usize index, void* memory)
    {
        char* addr = (char*) memory;

        if ( m_count == m_size ) return false;

        if ( m_size > index ) {
            if ( memory != 0 && m_memory[index] == 0 ) {
                m_memory[index] = addr;
                m_count += 1;

                return true;
            }
        }

        return false;
    }

    char*
    PageTable::remove(usize index)
    {
        char* addr = 0;

        if ( m_count == 0 ) return addr;

        if ( m_size > index ) {
            addr = m_memory[index];

            if ( m_memory[index] != 0 ) {
                m_memory[index] = 0;
                m_count -= 1;
            }
        }

        return addr;
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
