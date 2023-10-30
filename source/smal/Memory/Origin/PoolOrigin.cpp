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
        this->prepare(page);
    }

    usize
    PoolOrigin::size() const
    {
        return this->m_size;
    }

    usize
    PoolOrigin::count() const
    {
        return this->m_count;
    }

    usize
    PoolOrigin::page() const
    {
        return this->m_page;
    }

    bool
    PoolOrigin::prepare()
    {
        Node* node = (Node*) this->m_memory;
        Node* next = 0;
        char* addr = 0;

        if ( this->m_memory != 0 ) {
            this->m_count = Math::div(this->m_size, this->m_page);

            if ( this->m_count != 0 ) {
                this->m_list = node;

                for ( usize i = 0; i < this->m_count; i++ ) {
                    addr = (char*) node + this->m_page;
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
            this->m_page = page;
        else
            this->m_page = min;

        return this->prepare();
    }

    Page
    PoolOrigin::reserve(usize size)
    {
        Page page = {this, this->m_list, this->m_page};

        if ( size > this->m_page )
            return {};

        if ( this->m_count != 0 ) {
            this->m_count -= 1;
            this->m_list = this->m_list->next;

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
            node->next = this->m_list;

            page = {};

            this->m_list = node;
            this->m_count += 1;
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
            node->next = this->m_list;

            this->m_list = node;
            this->m_count += 1;
        }

        return true;
    }
} // namespace ma
