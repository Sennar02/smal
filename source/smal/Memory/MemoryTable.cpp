#include <smal/Memory/MemoryTable.hpp>

namespace ma
{
    const u32 MemoryTable::s_node_size =
        sizeof(char*);

    MemoryTable::MemoryTable()
        : m_memory {0}
        , m_size {0}
        , m_count {0}
    { }

    MemoryTable::MemoryTable(const FixedBuffer<char>& buffer)
        : MemoryTable()
    {
        m_memory = (char**) buffer.memory();
        m_size   = buffer.size();
    }

    MemoryTable::MemoryTable(void* memory, u32 size)
        : MemoryTable(FixedBuffer<char> {memory, size})
    { }

    char*
    MemoryTable::memory() const
    {
        return (char*) m_memory;
    }

    u32
    MemoryTable::size() const
    {
        return m_size;
    }

    u32
    MemoryTable::count() const
    {
        return m_count;
    }

    bool
    MemoryTable::isEmpty() const
    {
        return m_count == 0;
    }

    bool
    MemoryTable::isFull() const
    {
        return m_count == m_size;
    }

    bool
    MemoryTable::insert(void* memory)
    {
        u32 count = m_count;

        if ( m_count < m_size && memory != 0 )
            m_memory[m_count++] = (char*) memory;

        return m_count != count;
    }

    char*
    MemoryTable::remove()
    {
        char* addr = 0;

        if ( m_count != 0 )
            addr = m_memory[--m_count];

        return addr;
    }

    char*
    MemoryTable::find(u32 index) const
    {
        if ( index < m_count )
            return m_memory[index];

        return 0;
    }

    char*
    MemoryTable::convert(u32 byte, u32 page) const
    {
        return m_memory[byte / page] + (byte % page);
    }
} // namespace ma
