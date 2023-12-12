#include <smal/Memory/Alloc/PoolAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    PoolAlloc::PoolAlloc()
        : m_memory {0}
        , m_size {0}
        , m_count {0}
        , m_list {0}
        , m_page {s_node_size}
    { }

    PoolAlloc::PoolAlloc(void* memory, u32 size, u32 page)
        : m_memory {(char*) memory}
        , m_size {size}
        , m_count {0}
        , m_list {0}
        , m_page {s_node_size}
    {
        if ( m_memory == 0 )
            m_size = 0;

        prepare(page);
    }

    u32
    PoolAlloc::page() const
    {
        return m_page;
    }

    u32
    PoolAlloc::count() const
    {
        return m_count;
    }

    u32
    PoolAlloc::size() const
    {
        return m_size;
    }

    u32
    PoolAlloc::next() const
    {
        if ( m_count != 0 )
            return m_page;

        return 0;
    }

    char*
    PoolAlloc::memory() const
    {
        return m_memory;
    }

    bool
    PoolAlloc::contains(void* memory) const
    {
        char* inf = m_memory;
        char* sup = m_memory + m_size;

        return inf <= memory && memory < sup;
    }

    bool
    PoolAlloc::prepare()
    {
        Node* node = (Node*) m_memory;
        Node* next = 0;

        if ( m_memory != 0 ) {
            m_count = m_size / m_page;
            m_list  = (Node*) m_memory;

            memoryWipe(m_memory, m_size);

            for ( u32 i = 0; i < m_count - 1; i++ ) {
                next = (Node*) ((char*) node + m_page);

                node->next = next;
                node       = next;
            }
        }

        return m_memory != 0;
    }

    bool
    PoolAlloc::prepare(u32 page)
    {
        if ( m_page != page ) {
            m_page = page;

            if ( m_page < s_node_size )
                m_page = s_node_size;

            return prepare();
        }

        return true;
    }

    char*
    PoolAlloc::acquire(u32 size)
    {
        char* addr = (char*) m_list;

        if ( size == 0 ) return 0;
        if ( size == g_max_u32 ) size = m_page;

        if ( m_page >= size && m_count != 0 ) {
            m_count -= 1;
            m_list = m_list->next;

            return memoryWipe(addr, m_page);
        }

        return 0;
    }

    bool
    PoolAlloc::release(void* memory)
    {
        char* addr = (char*) memory;
        u32   dist = (addr - m_memory) % m_page;
        Node* node = (Node*) memory;

        if ( dist != 0 ) return false;

        if ( memory != 0 ) {
            if ( contains(node) == false )
                return false;

            for ( Node* iter = m_list; iter != 0; ) {
                if ( iter == memory )
                    return false;

                iter = iter->next;
            }

            m_count += 1;

            memoryWipe(memory, m_page);

            node->next = m_list;
            m_list     = node;
        }

        return true;
    }
} // namespace ma
