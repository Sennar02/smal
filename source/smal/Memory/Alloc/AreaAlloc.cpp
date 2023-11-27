#include <smal/Memory/Alloc/AreaAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    AreaAlloc::AreaAlloc()
        : BaseAlloc(0, 0)
        , m_cursor {0}
    { }

    AreaAlloc::AreaAlloc(void* memory, usize size)
        : BaseAlloc(memory, size)
        , m_cursor {0}
    {
        prepare();
    }

    usize
    AreaAlloc::avail() const
    {
        return m_size - (m_cursor - m_memory);
    }

    bool
    AreaAlloc::prepare()
    {
        m_cursor =
            m_memory;

        return true;
    }

    char*
    AreaAlloc::acquire(usize size)
    {
        char* addr = m_cursor + s_head_size;
        Head* head = (Head*) m_cursor;

        size += s_head_size;

        if ( m_cursor + size < m_memory + m_size ) {
            head->size = size - s_head_size;
            m_cursor += size;

            return memory_set(
                addr, size - s_head_size, 0);
        }

        return 0;
    }

    bool
    AreaAlloc::release(void* memory)
    {
        char* addr = (char*) memory;
        Head* head = (Head*) (addr - s_head_size);

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

    bool
    AreaAlloc::release()
    {
        return prepare();
    }
} // namespace ma
