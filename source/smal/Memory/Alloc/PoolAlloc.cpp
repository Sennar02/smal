#include <smal/Memory/Alloc/PoolAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    PoolAlloc::PoolAlloc()
        : m_memory {0}
        , m_list {0}
        , m_page {1}
        , m_count {0}
        , m_size {0}
    { }

    PoolAlloc::PoolAlloc(void* memory, u32 size, u32 page)
        : m_memory {(char*) memory}
        , m_list {0}
        , m_page {1}
        , m_count {0}
        , m_size {size}
    {
        if ( m_memory == 0 )
            m_size = 0;

        prepare(page);
    }

    u32
    PoolAlloc::size() const
    {
        return m_size;
    }

    char*
    PoolAlloc::memory()
    {
        return m_memory;
    }

    const char*
    PoolAlloc::memory() const
    {
        return m_memory;
    }

    bool
    PoolAlloc::contains(void* memory) const
    {
        char* addr = (char*) memory;

        if ( addr != 0 ) {
            return addr < m_memory + m_size &&
                   addr >= m_memory;
        }

        return true;
    }

    u32
    PoolAlloc::page() const
    {
        return m_page;
    }

    u32
    PoolAlloc::avail() const
    {
        return m_page * m_count;
    }

    bool
    PoolAlloc::prepare()
    {
        Node* node = (Node*) m_memory;
        Node* next = 0;

        if ( node != 0 ) {
            m_count = m_size / m_page;
            m_list  = (Node*)
                memorySet(m_memory, m_size, 0);

            for ( u32 i = 0; i < m_count - 1; i++ ) {
                next = (Node*) ((char*) node + m_page);

                node->next = next;
                node       = next;
            }
        }

        return node != 0;
    }

    bool
    PoolAlloc::prepare(u32 page)
    {
        if ( m_page == page ) return true;

        m_page = page;

        if ( m_page < sizeof(Node) )
            m_page = sizeof(Node);

        return prepare();
    }

    char*
    PoolAlloc::acquire(u32 size)
    {
        char* addr = (char*) m_list;

        if ( size == 0 ) return 0;
        if ( size == g_max_u32 ) size = 0;

        if ( m_page >= size && m_count != 0 ) {
            m_count -= 1;
            m_list = m_list->next;

            return memorySet(addr, m_page, 0);
        }

        return 0;
    }

    bool
    PoolAlloc::release(void* memory)
    {
        char* addr = (char*) memory;
        Node* node = 0;

        if ( contains(addr) == false )
            return false;

        if ( addr != 0 ) {
            node = (Node*)
                memorySet(addr, m_page, 0);

            m_count += 1;

            node->next = m_list;
            m_list     = node;
        }

        return true;
    }

    bool
    PoolAlloc::release()
    {
        return prepare();
    }
} // namespace ma
