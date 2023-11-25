#include <smal/Memory/Alloc/PoolAlloc.hpp>
#include <smal/Memory/helper.hpp>

namespace ma
{
    PoolAlloc::PoolAlloc()
        : BaseAlloc(0, 0)
    { }

    PoolAlloc::PoolAlloc(void* memory, usize size, usize page)
        : BaseAlloc(memory, size)
        , m_page {page}
    {
        if ( m_page == 0 )
            m_page = m_size;

        prepare();
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
        if ( page < sizeof(Node) )
            page = sizeof(Node);

        if ( m_page != page )
            return prepare();

        return true;
    }

    char*
    PoolAlloc::acquire(usize size)
    {
        char* addr  = (char*) m_list;
        usize count = m_size / m_page;

        if ( m_page >= size && count != 0 ) {
            m_list = m_list->next;

            return (char*) memory_set(
                addr, m_page, 0);
        }

        return 0;
    }

    bool
    PoolAlloc::release(char* addr)
    {
        Node* node = (Node*) addr;

        if ( contains(addr) ) return false;

        if ( addr != 0 ) {
            node->next = m_list;
            m_list     = node;
        }

        return true;
    }
} // namespace ma
