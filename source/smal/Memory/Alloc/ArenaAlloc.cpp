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
    ArenaAlloc::memory()
    {
        return m_memory;
    }

    const char*
    ArenaAlloc::memory() const
    {
        return m_memory;
    }

    bool
    ArenaAlloc::contains(void* memory) const
    {
        char* addr = (char*) memory;

        if ( addr != 0 ) {
            return addr < m_memory + m_size &&
                   addr >= m_memory;
        }

        return true;
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
            memorySet(m_memory, m_size, 0);

        return true;
    }

    char*
    ArenaAlloc::acquire(u32 size)
    {
        char* addr = m_cursor;

        if ( size == 0 ) return 0;

        if ( m_cursor + size <= m_memory + m_size ) {
            m_cursor += size;

            return memorySet(addr, size, 0);
        }

        return 0;
    }

    bool
    ArenaAlloc::release(void* memory)
    {
        return false;
    }

    bool
    ArenaAlloc::release()
    {
        return prepare();
    }
} // namespace ma
