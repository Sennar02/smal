#include <smal/Memory/Origin/ArenaOrigin.hpp>

#include <string.h> // memset

namespace ma
{
    ArenaOrigin::ArenaOrigin()
        : BaseOrigin()
        , m_pntr {0}
    { }

    ArenaOrigin::ArenaOrigin(const FixedBuffer<char>& buffer)
        : BaseOrigin(buffer)
        , m_pntr {0}
    {
        prepare();
    }

    ArenaOrigin::ArenaOrigin(void* memory, u32 size)
        : ArenaOrigin(FixedBuffer<char> {memory, size})
    { }

    bool
    ArenaOrigin::remains(u32 size) const
    {
        u32 dist = m_pntr - m_memory;
        u32 left = m_size - dist;

        return size <= left;
    }

    bool
    ArenaOrigin::prepare()
    {
        if ( m_memory != 0 )
            m_pntr = (char*) memset(m_memory, 0, m_size);

        return m_memory != 0;
    }

    char*
    ArenaOrigin::acquire(u32 size)
    {
        char* addr = 0;
        char* next = m_pntr + size;

        if ( size == 0 ) return 0;

        if ( next <= m_memory + m_size ) {
            addr   = m_pntr;
            m_pntr = next;

            memset(addr, 0, size);
        }

        return addr;
    }

    bool
    ArenaOrigin::release(void* memory)
    {
        return memory == 0;
    }
} // namespace ma
