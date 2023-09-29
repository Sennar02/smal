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

    PageTable::PageTable(void* memory, long length, long page)
        : m_memory {(Item*) memory}
        , m_length {length}
        , m_size {0}
        , m_page {page}
    { }

    long
    PageTable::get_length() const
    {
        return this->m_length;
    }

    long
    PageTable::get_size() const
    {
        return this->m_size;
    }

    long
    PageTable::get_page() const
    {
        return this->m_page;
    }

    bool
    PageTable::is_full() const
    {
        long length =
            this->m_size * sizeof(Item);

        return this->m_length == length;
    }

    bool
    PageTable::is_empty() const
    {
        return this->m_size == 0;
    }

    bool
    PageTable::insert(const Page& page, word offset)
    {
        if ( this->is_full() ) return false;

        if ( page.get_length() != this->m_page )
            return false;

        if ( page.is_null() == false ) {
            this->m_memory[this->m_size] = {
                .memory = page.get_memory(),
                .offset = offset,
            };

            this->m_size += 1;
        }

        return true;
    }

    bool
    PageTable::remove(const Page& page)
    {
        if ( this->is_empty() ) return false;

        if ( page.get_length() != this->m_page )
            return false;

        if ( page.is_null() == false ) {
            long index = this->search(page);

            if ( index != -1 ) {
                this->m_size -= 1;

                Common::swap(
                    this->m_memory[this->m_size],
                    this->m_memory[index]);
            }
        }

        return true;
    }

    char*
    PageTable::lookup(long index, long scale)
    {
        Item* item  = 0;
        long  start = 0;
        long  limit = 0;
        long  byte  = index * scale;

        for ( long i = 0; i < this->m_size; i++ ) {
            item = &this->m_memory[i];

            start = this->m_page * item->offset;
            limit = this->m_page + start;

            if ( start <= byte && byte < limit )
                return item->memory + (byte - start);
        }

        return 0;
    }

    long
    PageTable::search(const Page& page)
    {
        Item* item   = 0;
        char* memory = page.get_memory();

        for ( long i = 0; i < this->m_size; i++ ) {
            item = &this->m_memory[i];

            if ( item->memory == memory )
                return i;
        }

        return -1;
    }
} // namespace smal
