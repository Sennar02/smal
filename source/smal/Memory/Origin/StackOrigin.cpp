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
    StackOrigin::availab(u32 size) const
    {
        u32 diff = m_pntr - m_memory;
        u32 dist = m_size - diff;

        if ( size + s_head_size <= dist )
            return true;

        return false;
    }

    char*
    StackOrigin::acquire(u32 size)
    {
        u32   full = size + s_head_size;
        char* addr = m_pntr + s_head_size;
        char* next = m_pntr + full;
        Head* head = (Head*) m_pntr;

        if ( size == 0 ) return 0;

        if ( next <= m_memory + m_size ) {
            head->size = size;
            m_pntr     = next;

            return (char*)
                memset(addr, 0, size);
        }

        return 0;
    }

    bool
    StackOrigin::release(void* memory)
    {
        char* addr = (char*) memory;
        Head* head = (Head*) (addr - s_head_size);

        if ( memory != 0 ) {
            if ( contains(head) == false )
                return false;

            if ( m_pntr == addr + head->size )
                m_pntr = (char*) head;
            else
                return false;
        }

        return true;
    }
} // namespace ma
