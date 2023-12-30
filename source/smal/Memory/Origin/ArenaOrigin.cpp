#include <smal/Memory/Origin/ArenaOrigin.hpp>

#include <string.h> // memset

namespace ma
{
    ArenaOrigin::ArenaOrigin()
        : BaseOrigin()
        , m_pntr {0}
    { }

    ArenaOrigin::ArenaOrigin(void* memory, u32 size)
        : BaseOrigin(memory, size)
    {
        prepare();
    }

    bool
    ArenaOrigin::availab(u32 size) const
    {
        u32 diff = m_pntr - m_memory;
        u32 dist = m_size - diff;

        return size <= dist;
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
        char* addr = m_pntr;
        char* next = m_pntr + size;

        if ( size == 0 ) return 0;

        if ( next <= m_memory + m_size ) {
            m_pntr = next;

            return (char*)
                memset(addr, 0, size);
        }

        return 0;
    }

    bool
    ArenaOrigin::release(void* memory)
    {
        return memory == 0;
    }
} // namespace ma
