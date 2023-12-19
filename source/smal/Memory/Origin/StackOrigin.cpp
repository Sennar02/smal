#include <smal/Memory/Origin/StackOrigin.hpp>

#include <string.h> // memset

namespace ma
{
    struct Head
    {
        u32  size;
        char fill[4u];
    };

    static const u32 s_head_size =
        sizeof(Head);

    StackOrigin::StackOrigin()
        : ArenaOrigin()
    { }

    StackOrigin::StackOrigin(const FixedBuffer<char>& buffer)
        : ArenaOrigin(buffer)
    { }

    StackOrigin::StackOrigin(void* memory, u32 size)
        : ArenaOrigin(memory, size)
    { }

    bool
    StackOrigin::remains(u32 size) const
    {
        u32 dist = m_pntr - m_memory;
        u32 left = m_size - dist;

        if ( size + s_head_size <= left )
            return true;

        return false;
    }

    char*
    StackOrigin::acquire(u32 size)
    {
        u32   full = size + s_head_size;
        char* addr = 0;
        char* next = m_pntr + full;
        Head* head = (Head*) m_pntr;

        if ( size == 0 ) return 0;

        if ( next <= m_memory + m_size ) {
            head->size = size;
            addr       = m_pntr + s_head_size;
            m_pntr     = next;

            memset(addr, 0, size);
        }

        return addr;
    }

    bool
    StackOrigin::release(void* memory)
    {
        char* addr = (char*) memory;
        Head* head = (Head*) (addr - s_head_size);
        u32   size = s_head_size;

        if ( memory != 0 ) {
            if ( contains(head) == false )
                return false;

            size += head->size;

            if ( m_pntr != addr + head->size )
                return false;

            m_pntr = (char*)
                memset(head, 0, size);
        }

        return true;
    }
} // namespace ma
