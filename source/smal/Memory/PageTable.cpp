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

    Page
    PageTable::remove(long index)
    {
        Item* last = 0;

        if ( this->is_empty() ) return {};

        if ( 0 <= index && index < this->m_size ) {
            this->m_size -= 1;

            last = &Common::swap(
                this->m_memory[this->m_size],
                this->m_memory[index]);

            return {
                last->memory,
                this->m_page,
            };
        }

        return {};
    }

    char*
    PageTable::lookup(long index, long scale) const
    {
        long start = 0;
        long limit = 0;
        long byte  = index * scale;

        for ( long i = 0; i < this->m_size; i++ ) {
            start = this->m_page * this->m_memory[i].offset;
            limit = this->m_page + start;

            if ( start <= byte && byte < limit )
                return this->m_memory[i].memory + (byte - start);
        }

        return 0;
    }

} // namespace smal
