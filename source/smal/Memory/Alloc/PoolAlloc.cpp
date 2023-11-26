#include <smal/Memory/Alloc/PoolAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    PoolAlloc::PoolAlloc()
        : BaseAlloc(0, 0)
        , m_page {1}
    { }

    PoolAlloc::PoolAlloc(void* memory, usize size, usize page)
        : BaseAlloc(memory, size)
        , m_page {1}
    {
        prepare(page);
    }

    usize
    PoolAlloc::page() const
    {
        return m_page;
    }

    bool
    PoolAlloc::prepare()
    {
        Node* node  = (Node*) m_memory;
        Node* next  = 0;
        usize count = m_size / m_page;

        if ( node != 0 ) {
            m_list = node;

            for ( usize i = 0; i < count - 1; i++ ) {
                next = (Node*) ((char*) node + m_page);

                node->next = next;
                node       = next;
            }
        }

        return node != 0;
    }

    bool
    PoolAlloc::prepare(usize page)
    {
        if ( m_page == page ) return true;

        m_page = page;

        if ( m_page < sizeof(Node) )
            m_page = sizeof(Node);

        return prepare();
    }

    char*
    PoolAlloc::acquire(usize size)
    {
        char* addr  = (char*) m_list;
        usize count = m_size / m_page;

        if ( m_page >= size && count != 0 ) {
            m_list = m_list->next;

            return memory_set(
                addr, m_page, 0);
        }

        return 0;
    }

    bool
    PoolAlloc::release(void* memory)
    {
        char* addr = (char*) memory;
        Node* node = (Node*) addr;

        if ( contains(addr) == false )
            return false;

        if ( addr != 0 ) {
            node->next = m_list;
            m_list     = node;
        }

        return true;
    }
} // namespace ma
