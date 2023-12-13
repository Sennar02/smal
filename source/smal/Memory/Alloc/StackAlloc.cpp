#include <smal/Memory/Alloc/StackAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    union StackAlloc::Head
    {
        struct
        {
            u32 size;
        };

        char memory[16];
    };

    const u32 StackAlloc::s_head_size =
        sizeof(Head);

    StackAlloc::StackAlloc()
        : BaseAlloc()
        , m_cursor {0}
    { }

    StackAlloc::StackAlloc(void* memory, u32 size)
        : BaseAlloc(memory, size)
    {
        if ( memory != 0 && size != 0 )
            prepare();
    }

    bool
    StackAlloc::availab(u32 size) const
    {
        u32 dist = (m_cursor - m_memory) + s_head_size;

        return size <= m_size - dist;
    }

    bool
    StackAlloc::prepare()
    {
        if ( m_memory != 0 )
            m_cursor = memoryWipe(m_memory, m_size);

        return m_memory != 0;
    }

    char*
    StackAlloc::acquire(u32 size)
    {
        char* addr = m_cursor + s_head_size;
        Head* head = (Head*) m_cursor;

        u32   full = size + s_head_size;
        char* next = m_cursor + full;

        if ( size == 0 ) return 0;

        if ( next <= m_memory + m_size ) {
            head->size = size;
            m_cursor   = next;

            return memoryWipe(addr, size);
        }

        return 0;
    }

    bool
    StackAlloc::release(void* memory)
    {
        char* addr = (char*) memory - s_head_size;
        Head* head = (Head*) addr;
        u32   size = 0;

        if ( memory != 0 ) {
            if ( contains(addr) == false )
                return false;

            size = head->size + s_head_size;

            if ( m_cursor != addr + size )
                return false;

            m_cursor =
                memoryWipe(head, size);
        }

        return true;
    }
} // namespace ma
