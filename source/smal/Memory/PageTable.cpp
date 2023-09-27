#include <smal/Memory/PageTable.hpp>

namespace smal
{
    PageTable::PageTable()
        : m_memory {0}
        , m_length {0}
        , m_size {0}
    { }

    PageTable::PageTable(void* memory, long length)
        : m_memory {(Entry*) memory}
        , m_length {length}
        , m_size {0}
    { }

    bool
    PageTable::insert(Page& page, long offset)
    {
        if ( this->m_size < this->m_length ) {
            this->m_memory[this->m_size] = {
                .memory = page.get_memory(),
                .length = page.get_length(),
                .offset = offset,
            };

            this->m_size += 1;

            return true;
        }

        return false;
    }

    bool
    PageTable::remove(Page& page)
    {
        long index = this->search(page);

        if ( this->m_size > 0 ) {
            this->m_size -= 1;

            Common::swap(
                this->m_memory[this->m_size],
                this->m_memory[index]);

            return true;
        }

        return false;
    }

    Tuple<char*, long>
    PageTable::lookup(long index)
    {
        Tuple<char*, long> tuple;

        long offset = 0;
        long limit  = 0;

        for ( long i = 0; i < this->m_size; i++ ) {
            offset = this->m_memory[i].offset;
            limit  = this->m_memory[i].length + offset;

            if ( offset <= index && index < limit ) {
                tuple.get<0>() = this->m_memory[i].memory;
                tuple.get<1>() = index - offset;
            }
        }

        return tuple;
    }

    long
    PageTable::search(Page& page)
    {
        char* memory = page.get_memory();

        for ( long i = 0; i < this->m_size; i++ ) {
            if ( this->m_memory[i].memory == memory )
                return i;
        }

        return -1;
    }
} // namespace smal
