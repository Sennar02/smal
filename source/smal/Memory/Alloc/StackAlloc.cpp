#include <smal/Memory/Alloc/StackAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    StackAlloc::StackAlloc()
        : m_memory {0}
        , m_cursor {0}
        , m_size {0}
    { }

    StackAlloc::StackAlloc(void* memory, u32 size)
        : m_memory {(char*) memory}
        , m_cursor {0}
        , m_size {size}
    {
        if ( m_memory == 0 )
            m_size = 0;

        prepare();
    }

    u32
    StackAlloc::size() const
    {
        return m_size;
    }

    u32
    StackAlloc::avail() const
    {
        u32 size = m_size - (m_cursor - m_memory);

        if ( size > s_head_size )
            return size - s_head_size;

        return 0;
    }

    char*
    StackAlloc::memory() const
    {
        return m_memory;
    }

    bool
    StackAlloc::contains(void* memory) const
    {
        char* inf = m_memory;
        char* sup = m_memory + m_size;

        return inf <= memory && memory < sup;
    }

    bool
    StackAlloc::prepare()
    {
        m_cursor =
            memoryWipe(m_memory, m_size);

        return true;
    }

    char*
    StackAlloc::acquire(u32 size)
    {
        u32   full = s_head_size + size;
        char* addr = m_cursor + s_head_size;
        char* next = m_cursor + full;
        Head* head = (Head*) m_cursor;

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
