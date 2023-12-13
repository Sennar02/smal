#include <smal/Memory/Alloc/ArenaAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    ArenaAlloc::ArenaAlloc()
        : BaseAlloc()
        , m_cursor {0}
    { }

    ArenaAlloc::ArenaAlloc(void* memory, u32 size)
        : BaseAlloc(memory, size)
    {
        if ( memory != 0 && size != 0 )
            prepare();
    }

    bool
    ArenaAlloc::availab(u32 size) const
    {
        u32 diff = m_cursor - m_memory;

        return size <= m_size - diff;
    }

    bool
    ArenaAlloc::prepare()
    {
        if ( m_memory != 0 )
            m_cursor = memoryWipe(m_memory, m_size);

        return m_memory != 0;
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
