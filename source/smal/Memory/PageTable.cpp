#include <smal/Memory/PageTable.hpp>

namespace ma
{
    PageTable::PageTable()
        : m_memory {0}
        , m_length {0}
        , m_count {0}
    { }

    PageTable::PageTable(void* memory, u32 length)
        : PageTable()
    {
        if ( memory != 0 && length != 0 ) {
            m_memory = (Item*) memory;
            m_length = length;
        }
    }

    char*
    PageTable::memory() const
    {
        return (char*) m_memory;
    }

    u32
    PageTable::length() const
    {
        return m_length;
    }

    u32
    PageTable::count() const
    {
        return m_count;
    }

    bool
    PageTable::isEmpty() const
    {
        return m_count == 0;
    }

    bool
    PageTable::isFull() const
    {
        return m_count == m_length;
    }

    bool
    PageTable::insert(void* memory)
    {
        u32 count = m_count;

        if ( m_count < m_length && memory != 0 )
            m_memory[m_count++] = (Item) memory;

        return m_count != count;
    }

    char*
    PageTable::remove()
    {
        char* addr = 0;

        if ( m_count != 0 )
            addr = m_memory[--m_count];

        return addr;
    }

    char*
    PageTable::find(u32 index) const
    {
        if ( index < m_count )
            return m_memory[index];

        return 0;
    }

    char*
    PageTable::convert(u32 byte, u32 page) const
    {
        return m_memory[byte / page] + (byte % page);
    }
} // namespace ma
