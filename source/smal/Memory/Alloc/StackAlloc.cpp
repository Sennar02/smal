#include <smal/Memory/Alloc/StackAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    StackAlloc::StackAlloc()
        : BaseAlloc(0, 0)
        , m_cursor {0}
    { }

    StackAlloc::StackAlloc(void* memory, usize size)
        : BaseAlloc(memory, size)
        , m_cursor {0}
    {
        prepare();
    }

    bool
    StackAlloc::prepare()
    {
        m_cursor =
            m_memory;

        return true;
    }

    char*
    StackAlloc::acquire(usize size)
    {
        char* addr = m_cursor + g_head_size;
        Head* head = (Head*) m_cursor;

        size += g_head_size;

        if ( m_cursor + size < m_memory + m_size ) {
            head->size = size - g_head_size;
            m_cursor += size;

            return memory_set(
                addr, size - g_head_size, 0);
        }

        return 0;
    }

    bool
    StackAlloc::release(void* memory)
    {
        char* addr = (char*) memory;
        Head* head = (Head*) (addr - g_head_size);

        if ( contains(addr) == false )
            return false;

        if ( addr != 0 ) {
            if ( m_cursor == addr + head->size )
                m_cursor = (char*) head;
            else
                return false;
        }

        return true;
    }
} // namespace ma
