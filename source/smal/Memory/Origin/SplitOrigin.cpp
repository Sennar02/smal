#include <smal/Memory/Origin/SplitOrigin.hpp>

#include <string.h> // memset

namespace ma
{
    struct Head
    {
        u32  size;
        bool used;
        char fill[3u];
    };

    static const u32 s_head_size =
        sizeof(Head);

    SplitOrigin::SplitOrigin()
        : BaseOrigin()
        , m_unit {1}
    { }

    SplitOrigin::SplitOrigin(void* memory, u32 size, u32 unit)
        : BaseOrigin(memory, size)
        , m_unit {1}
    {
        prepare(unit);
    }

    u32
    SplitOrigin::unit() const
    {
        return m_unit - s_head_size;
    }

    bool
    SplitOrigin::availab(u32 size) const
    {
        char* addr = m_memory;
        Head* head = (Head*) m_memory;

        if ( size < m_unit ) size = m_unit;

        while ( addr < m_memory + m_size ) {
            addr += head->size;

            if ( head->used == false ) {
                if ( head->size >= size + s_head_size )
                    return true;
            }

            head = (Head*) addr;
        }

        return false;
    }

    bool
    SplitOrigin::prepare(u32 unit)
    {
        Head* head = (Head*) m_memory;

        if ( unit < s_head_size ) return false;

        if ( m_memory != 0 ) {
            memset(m_memory, 0, m_size);

            m_unit     = unit + s_head_size;
            head->size = m_size;
        }

        return m_memory != 0;
    }

    bool
    SplitOrigin::prepare()
    {
        return prepare(m_unit - s_head_size);
    }

    char*
    SplitOrigin::acquire(u32 size)
    {
        Head* head = (Head*) split(size);
        char* addr = (char*) head + s_head_size;

        if ( head != 0 ) {
            size       = head->size - s_head_size;
            head->used = true;

            return (char*)
                memset(addr, 0, size);
        }

        return 0;
    }

    bool
    SplitOrigin::release(void* memory)
    {
        char* addr = (char*) memory;
        Head* head = (Head*) (addr - s_head_size);

        if ( memory != 0 ) {
            if ( contains(memory) == false )
                return false;

            if ( head->used ) {
                head->used = false;
                merge();
            } else
                return false;
        }

        return true;
    }

    void*
    SplitOrigin::search(u32 size) const
    {
        char* addr = m_memory;
        Head* head = (Head*) m_memory;
        Head* best = 0;

        if ( size < m_unit ) size = m_unit;

        while ( addr < m_memory + m_size ) {
            addr += head->size;

            if ( head->used == false ) {
                if ( head->size >= size + s_head_size ) {
                    if ( best == 0 || best->size > head->size )
                        best = head;
                }
            }

            head = (Head*) addr;
        }

        return best;
    }

    void*
    SplitOrigin::split(u32 size) const
    {
        Head* head = (Head*) search(size);
        Head* next = 0;
        u32   half = 0;

        if ( size < m_unit ) size = m_unit;

        if ( head != 0 ) {
            half = head->size / 2u;

            for ( ; size <= half; half /= 2u ) {
                next = (Head*) ((char*) head + half);

                next->size = head->size - half;
                head->size = half;
            }
        }

        return head;
    }

    void
    SplitOrigin::merge() const
    {
        char* addr = 0;
        Head* head = 0;
        Head* next = 0;

        for ( bool loop = true; loop; ) {
            addr = m_memory;
            head = (Head*) m_memory;
            loop = false;

            while ( addr < m_memory + m_size ) {
                addr = (char*) head + head->size;
                next = (Head*) addr;

                if ( addr >= m_memory + m_size ) break;

                if ( next->size == head->size - 1u ||
                     next->size == head->size ) {
                    if ( head->used || next->used ) {
                        addr = (char*) next + next->size;
                        head = (Head*) addr;
                    } else {
                        head->size += next->size;
                        loop = true;
                    }
                } else
                    head = next;
            }
        }
    }
} // namespace ma
