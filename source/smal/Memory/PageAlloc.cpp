#include <smal/Memory/PageAlloc.hpp>
#include <smal/Memory/helper.hpp>

namespace smal
{
    PageAlloc::PageAlloc()
        : m_memory {0}
        , m_length {0}
        , m_list {0}
        , m_size {0}
    { }

    PageAlloc::PageAlloc(void* memory, long length, long page)
        : m_memory {(char*) memory}
        , m_length {length}
        , m_list {0}
        , m_size {0}
        , m_page {0}
    {
        this->prepare(page);
    }

    long
    PageAlloc::length() const
    {
        return this->m_length;
    }

    long
    PageAlloc::size() const
    {
        return this->m_size;
    }

    long
    PageAlloc::page() const
    {
        return this->m_page;
    }

    bool
    PageAlloc::prepare()
    {
        Node* node = (Node*) this->m_memory;
        Node* next = 0;
        char* addr = 0;

        if ( this->m_memory != 0 ) {
            this->m_size = Math::div(this->m_length, this->m_page);

            if ( this->m_size != 0 ) {
                this->m_list = node;

                for ( long i = 0; i < this->m_size; i++ ) {
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
    PageAlloc::prepare(long page)
    {
        if ( page > 0 )
            this->m_page = page;

        return this->prepare();
    }

    Page
    PageAlloc::reserve()
    {
        Page page = {this, this->m_list, this->m_page};

        if ( this->m_list != 0 ) {
            this->m_list = this->m_list->next;
            this->m_size -= 1;

            Memory::set(
                page.memory(),
                page.length(),
                0);
        }

        return page;
    }

    bool
    PageAlloc::reclaim(const Page& page)
    {
        Node* node = (Node*) page.memory();

        if ( page.origin() != this )
            return false;

        if ( page.isNull() == false ) {
            node->next = this->m_list;

            this->m_list = node;
            this->m_size += 1;
        }

        return true;
    }
} // namespace smal
