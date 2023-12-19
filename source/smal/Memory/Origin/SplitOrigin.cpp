#include <smal/Memory/Origin/SplitOrigin.hpp>

#include <string.h> // memset

namespace ma
{
    struct Head
    {
        u32  size;
        bool used;
    };

    static const u32 s_head_size =
        sizeof(Head);

    SplitOrigin::SplitOrigin()
        : BaseOrigin()
        , m_unit {1}
    { }

    SplitOrigin::SplitOrigin(const FixedBuffer<char>& buffer, u32 unit)
        : BaseOrigin(buffer)
        , m_unit {1}
    {
        prepare(unit);
    }

    SplitOrigin::SplitOrigin(void* memory, u32 size, u32 unit)
        : SplitOrigin(FixedBuffer<char> {memory, size}, unit)
    { }

    u32
    SplitOrigin::unit() const
    {
        return m_unit - s_head_size;
    }

    bool
    SplitOrigin::remains(u32 size) const
    {
        char* addr = m_memory;
        Head* head = (Head*) m_memory;

        if ( size < m_unit ) size = m_unit;

        while ( addr < m_memory + m_size ) {
            addr += head->size;

            if ( head->used == false && head->size >= size )
                return true;

            head = (Head*) addr;
        }

        return false;
    }

    bool
    SplitOrigin::prepare(u32 unit)
    {
        Head* head = 0;

        if ( unit < s_head_size ) return false;

        if ( m_memory != 0 ) {
            head = (Head*) memset(m_memory, 0, m_size);

            m_unit     = unit + s_head_size;
            head->size = m_size;
        }

        return m_memory != 0;
    }

    bool
    SplitOrigin::prepare()
    {
        return prepare(m_unit);
    }

    char*
    SplitOrigin::acquire(u32 size)
    {
        u32   full = size + s_head_size;
        Head* head = (Head*) split(full);
        char* addr = (char*) head + s_head_size;

        if ( head != 0 ) {
            size       = head->size - s_head_size;
            head->used = true;

            return (char*) memset(addr, 0, size);
        }

        return 0;
    }

    bool
    SplitOrigin::release(void* memory)
    {
        char* addr = (char*) memory;
        Head* head = (Head*) (addr - s_head_size);
        u32   size = 0;

        if ( memory != 0 ) {
            if ( contains(memory) == false )
                return false;

            size = head->size - s_head_size;

            if ( head->used == false )
                return false;

            memset(addr, 0, size);

            head->used = false;

            return merge();
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

            if ( head->used == false && head->size >= size ) {
                if ( best == 0 || best->size > head->size )
                    best = head;
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
                next = (Head*) memsum(head, half);

                next->size = head->size - half;
                head->size = half;
            }
        }

        return head;
    }

    bool
    SplitOrigin::merge() const
    {
        Head* head = (Head*) m_memory;
        Head* next = 0;

        if ( m_memory == 0 ) return false;

        while ( head->size != m_size ) {
            next = (Head*) memsum(head, head->size);

            if ( head->used || next->used ) break;

            if ( head->size != next->size - 1u &&
                 head->size != next->size ) break;

            head->size += next->size;
            next->size = 0;
            next->used = false;
        }

        return true;
    }
} // namespace ma
