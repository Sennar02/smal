#include <smal/Memory/PageTable.hpp>

namespace smal
{
    PageTable::PageTable()
        : m_memory {0}
        , m_length {0}
        , m_size {0}
    { }

    PageTable::PageTable(void* memory, long length)
        : m_memory {(Record*) memory}
        , m_length {length}
        , m_size {0}
    { }

    bool
    PageTable::insert(Page& page, long start)
    {
        Record* record = 0;

        if ( this->m_size < this->m_length ) {
            record = &this->m_memory[this->m_size];

            this->m_size += 1;

            record->memory = page.get_memory();
            record->length = page.get_length();
            record->start  = start;

            return true;
        }

        return false;
    }

    bool
    PageTable::remove(Page& page)
    {
        return false;
    }

    Tuple<char*, long>
    PageTable::lookup(long index)
    {
        Tuple<char*, long> tuple;

        long start = 0;
        long limit = 0;

        for ( long i = 0; i < this->m_size; i++ ) {
            start = this->m_memory[i].start;
            limit = this->m_memory[i].length + start;

            if ( start <= index && index < limit ) {
                tuple.get<0>() = this->m_memory[i].memory;
                tuple.get<1>() = index - start;
            }
        }

        return tuple;
    }
} // namespace smal
