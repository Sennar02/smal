#include <smal/Memory/Alloc/ArenaAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    ArenaAlloc::ArenaAlloc()
        : m_memory {0}
        , m_cursor {0}
        , m_size {0}
    { }

    ArenaAlloc::ArenaAlloc(void* memory, u32 size)
        : m_memory {(char*) memory}
        , m_cursor {0}
        , m_size {size}
    {
        if ( m_memory == 0 )
            m_size = 0;

        prepare();
    }

    u32
    ArenaAlloc::size() const
    {
        return m_size;
    }

    char*
    ArenaAlloc::memory() const
    {
        return m_memory;
    }

    bool
    ArenaAlloc::contains(void* memory) const
    {
        char* inf = m_memory;
        char* sup = m_memory + m_size;

        return inf <= memory && memory < sup;
    }

    u32
    ArenaAlloc::avail() const
    {
        return m_size - (m_cursor - m_memory);
    }

    bool
    ArenaAlloc::prepare()
    {
        m_cursor =
            memoryWipe(m_memory, m_size);

        return true;
    }

    char*
    ArenaAlloc::acquire(u32 size)
    {
        char* addr = m_cursor;
        char* next = m_cursor + size;

        if ( size == 0 ) return 0;

        if ( next <= m_memory + m_size ) {
            m_cursor = next;

            return memoryWipe(addr, size);
        }

        return 0;
    }

    bool
    ArenaAlloc::release(void* memory)
    {
        return memory == 0;
    }
} // namespace ma
