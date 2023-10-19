#include <smal/Memory/Origin/PoolOrigin.hpp>
#include <smal/Memory/helper.hpp>

namespace smal
{
    PoolOrigin::PoolOrigin()
        : m_memory {0}
        , m_length {0}
        , m_list {0}
        , m_size {0}
    { }

    PoolOrigin::PoolOrigin(void* memory, usize length, usize page)
        : m_memory {(char*) memory}
        , m_length {length}
        , m_list {0}
        , m_size {0}
        , m_page {0}
    {
        this->prepare(Math::max(page, 8lu));
    }

    usize
    PoolOrigin::length() const
    {
        return this->m_length;
    }

    usize
    PoolOrigin::size() const
    {
        return this->m_size;
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
            this->m_size = Math::div(this->m_length, this->m_page);

            if ( this->m_size != 0 ) {
                this->m_list = node;

                for ( usize i = 0; i < this->m_size; i++ ) {
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
        if ( page >= sizeof(void*) )
            this->m_page = page;

        return this->prepare();
    }

    Page
    PoolOrigin::reserve(usize length)
    {
        Page page = {this, this->m_list, this->m_page};

        if ( length > this->m_page )
            return {};

        if ( this->m_size != 0 ) {
            this->m_size -= 1;
            this->m_list = this->m_list->next;

            Memory::set(
                page.memory(),
                page.length(),
                0);

            return page;
        }

        return {};
    }

    bool
    PoolOrigin::reclaim(Page& page)
    {
        Node* node = (Node*) page.memory();

        if ( page.origin() != this && page.origin() != 0 )
            return false;

        if ( page.isNull() == false ) {
            node->next = this->m_list;

            page = {};

            this->m_list = node;
            this->m_size += 1;
        }

        return true;
    }

    bool
    PoolOrigin::reclaim(Page&& page)
    {
        Node* node = (Node*) page.memory();

        if ( page.origin() != this && page.origin() != 0 )
            return false;

        if ( page.isNull() == false ) {
            node->next = this->m_list;

            this->m_list = node;
            this->m_size += 1;
        }

        return true;
    }
} // namespace smal
