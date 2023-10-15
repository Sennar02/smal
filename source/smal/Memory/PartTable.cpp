#include <smal/Memory/PartTable.hpp>
#include <smal/Memory/Origin/PoolOrigin.hpp>

namespace smal
{
    PartTable::PartTable()
        : m_memory {0}
        , m_length {0}
        , m_size {0}
        , m_page {0}
    { }

    PartTable::PartTable(void* memory, usize length, usize page)
        : m_memory {(char**) memory}
        , m_length {length}
        , m_size {0}
        , m_page {page}
    {
        this->m_length /= sizeof(char*);
    }

    usize
    PartTable::length() const
    {
        return this->m_length * sizeof(char*);
    }

    usize
    PartTable::size() const
    {
        return this->m_size;
    }

    usize
    PartTable::page() const
    {
        return this->m_page;
    }

    bool
    PartTable::isFull() const
    {
        return this->m_size == this->m_length;
    }

    bool
    PartTable::isEmpty() const
    {
        return this->m_size == 0;
    }

    bool
    PartTable::insert(const Part& page, usize index)
    {
        char* memory = (char*) page.memory();

        if ( index >= this->m_length )
            return false;

        if ( page.isNull() == false ) {
            if ( this->m_memory[index] != 0 )
                return false;

            this->m_size += 1;
            this->m_memory[index] = memory;

            return true;
        }

        return false;
    }

    char*
    PartTable::remove(usize index)
    {
        char* memory = 0;

        if ( index < this->m_length ) {
            memory = this->m_memory[index];

            this->m_memory[index] = 0;
            this->m_size -= 1;
        }

        return memory;
    }

    char*
    PartTable::lookup(usize index, usize scale) const
    {
        usize byte = index * scale;

        usize page = Math::div(byte, this->m_page);
        usize dist = Math::mod(byte, this->m_page);

        if ( page < this->m_length && this->m_memory[page] != 0 )
            return this->m_memory[page] + dist;

        return 0;
    }
} // namespace smal
