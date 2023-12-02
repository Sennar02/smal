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

    char*
    StackAlloc::memory()
    {
        return m_memory;
    }

    const char*
    StackAlloc::memory() const
    {
        return m_memory;
    }

    bool
    StackAlloc::contains(void* memory) const
    {
        char* addr = (char*) memory;

        if ( addr != 0 ) {
            return addr < m_memory + m_size &&
                   addr >= m_memory;
        }

        return true;
    }

    u32
    StackAlloc::avail() const
    {
        u32 size = m_size - (m_cursor - m_memory);

        if ( size > s_head_size )
            return size - s_head_size;

        return 0;
    }

    bool
    StackAlloc::prepare()
    {
        m_cursor =
            memorySet(m_memory, m_size, 0);

        return true;
    }

    char*
    StackAlloc::acquire(u32 size)
    {
        char* addr = m_cursor + s_head_size;
        Head* head = (Head*) m_cursor;

        if ( size == 0 ) return 0;

        size += s_head_size;

        if ( m_cursor + size <= m_memory + m_size ) {
            m_cursor += size;

            size -= s_head_size;
            head->size = size;

            return memorySet(addr, size, 0);
        }

        return 0;
    }

    bool
    StackAlloc::release(void* memory)
    {
        char* addr = (char*) memory;
        Head* head = (Head*) (addr - s_head_size);

        if ( contains(addr) == false )
            return false;

        if ( addr != 0 ) {
            if ( m_cursor == addr + head->size ) {
                head->size += s_head_size;

                m_cursor =
                    memorySet(head, head->size, 0);
            } else
                return false;
        }

        return true;
    }

    bool
    StackAlloc::release()
    {
        return prepare();
    }
} // namespace ma
