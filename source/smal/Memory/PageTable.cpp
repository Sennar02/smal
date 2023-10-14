#include <smal/Memory/PageTable.hpp>
#include <smal/Memory/PageAlloc.hpp>

namespace smal
{
    PageTable::PageTable()
        : m_memory {0}
        , m_length {0}
        , m_size {0}
        , m_page {0}
    { }

    PageTable::PageTable(void* memory, usize length, usize page)
        : m_memory {(Item*) memory}
        , m_length {length}
        , m_size {0}
        , m_page {page}
    {
        this->m_length /= sizeof(Item);
    }

    usize
    PageTable::length() const
    {
        return this->m_length * sizeof(Item);
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
    PageTable::isFull() const
    {
        return this->m_size == this->m_length;
    }

    bool
    PageTable::isEmpty() const
    {
        return this->m_size == 0;
    }

    bool
    PageTable::insert(const Part& page, usize offset)
    {
        if ( offset >= this->m_length )
            return false;

        if ( page.isNull() == false ) {
            if ( this->m_memory[offset] != 0 )
                return false;

            this->m_memory[offset] = page.memory();
            this->m_size += 1;

            return true;
        }

        return false;
    }

    char*
    PageTable::remove(usize offset)
    {
        char* memory = 0;

        if ( offset < this->m_length ) {
            memory = this->m_memory[offset];

            this->m_memory[offset] = 0;
            this->m_size -= 1;
        }

        return memory;
    }

    char*
    PageTable::lookup(usize index, usize scale) const
    {
        usize byte = index * scale;

        usize page = Math::div(byte, this->m_page);
        usize dist = Math::mod(byte, this->m_page);

        if ( page < this->m_length && this->m_memory[page] != 0 )
            return this->m_memory[page] + dist;

        return 0;
    }
} // namespace smal
