#include <smal/Memory/Alloc/SplitAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    union SplitAlloc::Head
    {
        struct
        {
            u32  size;
            u32  prev;
            bool used;
        };

        char memory[16];

        static Head*
        forw(Head* self, u32 size)
        {
            char* addr = (char*) self;
            char* next = addr + size;

            return (Head*) next;
        }

        static Head*
        forw(Head* self)
        {
            char* addr = (char*) self;
            char* next = addr + self->size;

            return (Head*) next;
        }

        static Head*
        back(Head* self)
        {
            char* addr = (char*) self;
            char* next = addr - self->prev;

            return (Head*) next;
        }
    };

    const u32 SplitAlloc::s_head_size =
        sizeof(Head);

    SplitAlloc::SplitAlloc()
        : BaseAlloc()
        , m_unit {s_head_size}
    { }

    SplitAlloc::SplitAlloc(void* memory, u32 size, u32 unit)
        : BaseAlloc(memory, size)
        , m_unit {s_head_size}
    {
        if ( unit >= s_head_size ) {
            if ( memory != 0 && size != 0 )
                prepare(unit);
        }
    }

    u32
    SplitAlloc::unit() const
    {
        return m_unit;
    }

    bool
    SplitAlloc::availab(u32 size) const
    {
        char* addr = m_memory;
        Head* node = (Head*) addr;

        if ( size > s_head_size ) {
            while ( addr < m_memory + m_size ) {
                addr += node->size;

                if ( node->used == false && size <= node->size )
                    return true;

                node = (Head*) addr;
            }
        }

        return false;
    }

    bool
    SplitAlloc::prepare(u32 unit)
    {
        Head* root = (Head*)
            memoryWipe(m_memory, m_size);

        if ( unit < s_head_size ) return false;

        if ( m_memory != 0 ) {
            root->size = m_size;
            m_unit     = unit;
        }

        return m_memory != 0;
    }

    bool
    SplitAlloc::prepare()
    {
        return prepare(m_unit);
    }

    void*
    SplitAlloc::split(void* memory, u32 size) const
    {
        Head* node = (Head*) memory;
        Head* next = 0;
        u32   half = node->size / 2;

        if ( size < m_unit ) size = m_unit;

        if ( node != 0 ) {
            for ( ; size <= half; half /= 2 ) {
                next = Head::forw(node, half);

                next->size = node->size - half;
                next->prev = half;
                node->size = half;
            }

            if ( size <= node->size )
                return node;
        }

        return 0;
    }

    void*
    SplitAlloc::merge(void* memory) const
    {
        Head* node = (Head*) memory;
        Head* next = 0;

        if ( node == 0 ) return 0;

        while ( node->prev != 0 ) {
            next = node;
            node = Head::back(node);

            if ( node->used || next->used ) break;

            if ( node->size != next->size - 1 &&
                 node->size != next->size ) break;

            node->size += next->size;
        }

        while ( node->size != m_size ) {
            next = Head::forw(node);

            if ( node->used || next->used ) break;

            if ( node->size != next->size - 1 &&
                 node->size != next->size ) break;

            node->size += next->size;
        }

        return node;
    }

    void*
    SplitAlloc::search(u32 size) const
    {
        char* addr = m_memory;
        Head* node = (Head*) addr;
        Head* best = 0;

        if ( size > s_head_size ) {
            while ( addr < m_memory + m_size ) {
                addr += node->size;

                if ( node->used == false && size <= node->size ) {
                    if ( best == 0 || node->size < best->size )
                        best = node;
                }

                node = (Head*) addr;
            }
        }

        return best;
    }

    char*
    SplitAlloc::acquire(u32 size)
    {
        u32   full = size + s_head_size;
        Head* head = (Head*) search(full);
        char* addr = (char*) head + s_head_size;

        if ( size == 0 ) return 0;

        if ( head != 0 && split(head, full) != 0 ) {
            head->used = true;
            size       = head->size - s_head_size;

            return memoryWipe(addr, size);
        }

        return 0;
    }

    bool
    SplitAlloc::release(void* memory)
    {
        char* addr = (char*) memory;
        Head* head = (Head*) (addr - s_head_size);
        u32   size = 0;

        if ( memory != 0 ) {
            if ( contains(addr) == false )
                return false;

            if ( head->used == false )
                return false;

            size       = head->size - s_head_size;
            head->used = false;

            memoryWipe(addr, size);

            return merge(head) != 0;
        }

        return true;
    }
} // namespace ma
