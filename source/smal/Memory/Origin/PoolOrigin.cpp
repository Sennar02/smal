#include <smal/Memory/Origin/PoolOrigin.hpp>
#include <smal/Memory/helper.hpp>

namespace ma
{
    PoolOrigin::PoolOrigin()
        : m_memory {0}
        , m_size {0}
        , m_list {0}
        , m_count {0}
    { }

    PoolOrigin::PoolOrigin(void* memory, usize size, usize page)
        : m_memory {(char*) memory}
        , m_size {size}
        , m_list {0}
        , m_count {0}
        , m_page {0}
    {
        prepare(page);
    }

    usize
    PoolOrigin::size() const
    {
        return m_size;
    }

    usize
    PoolOrigin::count() const
    {
        return m_count;
    }

    usize
    PoolOrigin::page() const
    {
        return m_page;
    }

    bool
    PoolOrigin::prepare()
    {
        Node* node = (Node*) m_memory;
        Node* next = 0;
        char* addr = 0;

        if ( m_memory != 0 ) {
            m_count = Math::div(m_size, m_page);

            if ( m_count != 0 ) {
                m_list = node;

                for ( usize i = 0; i < m_count; i++ ) {
                    addr = (char*) node + m_page;
                    next = (Node*) addr;

                    node->next = next;
                    node       = next;
                }

                return true;
            }
        }

        return false;
    }

    bool
    PoolOrigin::prepare(usize page)
    {
        usize min = sizeof(Node);

        if ( page >= min )
            m_page = page;
        else
            m_page = min;

        return prepare();
    }

    Page
    PoolOrigin::reserve(usize size)
    {
        Page page = {this, m_list, m_page};

        if ( size > m_page )
            return {};

        if ( m_count != 0 ) {
            m_count -= 1;
            m_list = m_list->next;

            Memory::set(
                page.memory(),
                page.size(),
                0);

            return page;
        }

        return {};
    }

    bool
    PoolOrigin::reclaim(Page& page)
    {
        Node* node = (Node*) page.memory();

        if ( page.origin() != this &&
             page.origin() != 0 )
            return false;

        if ( page.is_null() == false ) {
            node->next = m_list;

            page = {};

            m_list = node;
            m_count += 1;
        }

        return true;
    }

    bool
    PoolOrigin::reclaim(Page&& page)
    {
        Node* node = (Node*) page.memory();

        if ( page.origin() != this &&
             page.origin() != 0 )
            return false;

        if ( page.is_null() == false ) {
            node->next = m_list;

            m_list = node;
            m_count += 1;
        }

        return true;
    }
} // namespace ma
