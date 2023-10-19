#include <smal/Memory/PageTable.hpp>
#include <smal/Memory/Origin/PoolOrigin.hpp>

namespace smal
{
    PageTable::PageTable()
        : m_memory {0}
        , m_length {0}
        , m_size {0}
        , m_page {0}
    { }

    PageTable::PageTable(const Page& page)
        : PageTable((void*) page.memory(), page.length(), page.length())
    { }

    PageTable::PageTable(void* memory, usize length, usize page)
        : m_memory {(Node*) memory}
        , m_length {length}
        , m_size {0}
        , m_page {page}
    {
        this->m_length /= sizeof(Node);
    }

    usize
    PageTable::length() const
    {
        return this->m_length;
    }

    usize
    PageTable::size() const
    {
        return this->m_size;
    }

    usize
    PageTable::page() const
    {
        return this->m_page;
    }

    bool
    PageTable::isEmpty() const
    {
        return this->m_size == 0;
    }

    bool
    PageTable::isFull() const
    {
        return this->m_size == this->m_length;
    }

    bool
    PageTable::insert(usize key, const Page& page)
    {
        char* memory = (char*) page.memory();

        if ( key >= this->m_length )
            return false;

        if ( page.length() == this->m_page &&
             page.isNull() == false ) {
            if ( this->m_memory[key] != 0 )
                return false;

            this->m_size += 1;
            this->m_memory[key] = memory;

            return true;
        }

        return false;
    }

    char*
    PageTable::remove(usize key)
    {
        char* memory = 0;

        if ( key < this->m_length ) {
            if ( this->m_memory[key] != 0 ) {
                memory = this->m_memory[key];

                this->m_size -= 1;
                this->m_memory[key] = 0;
            }
        }

        return memory;
    }

    char*
    PageTable::lookup(usize index) const
    {
        usize page = Math::div(index, this->m_page);
        usize byte = Math::mod(index, this->m_page);

        return this->m_memory[page] + byte;
    }
} // namespace smal
