#include <smal/Memory/Alloc/PageAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    PageAlloc::PageAlloc()
        : BaseAlloc(0, 0)
        , m_page {1}
        , m_count {0}
    { }

    PageAlloc::PageAlloc(void* memory, usize size, usize page)
        : BaseAlloc(memory, size)
        , m_page {1}
        , m_count {0}
    {
        prepare(page);
    }

    usize
    PageAlloc::page() const
    {
        return m_page;
    }

    usize
    PageAlloc::avail() const
    {
        return m_count * m_page;
    }

    bool
    PageAlloc::prepare()
    {
        Node* node = (Node*) m_memory;
        Node* next = 0;

        if ( node != 0 ) {
            m_count = m_size / m_page;
            m_list  = node;

            for ( usize i = 0; i < m_count - 1; i++ ) {
                next = (Node*) ((char*) node + m_page);

                node->next = next;
                node       = next;
            }
        }

        return node != 0;
    }

    bool
    PageAlloc::prepare(usize page)
    {
        if ( m_page == page ) return true;

        m_page = page;

        if ( m_page < sizeof(Node) )
            m_page = sizeof(Node);

        return prepare();
    }

    char*
    PageAlloc::acquire(usize size)
    {
        char* addr = (char*) m_list;

        if ( m_page >= size && m_count != 0 ) {
            m_count -= 1;
            m_list = m_list->next;

            return memory_set(
                addr, m_page, 0);
        }

        return 0;
    }

    bool
    PageAlloc::release(void* memory)
    {
        char* addr = (char*) memory;
        Node* node = (Node*) addr;

        if ( contains(addr) == false )
            return false;

        if ( addr != 0 ) {
            m_count += 1;

            node->next = m_list;
            m_list     = node;
        }

        return true;
    }

    bool
    PageAlloc::release()
    {
        return prepare();
    }
} // namespace ma
