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
    PageTable::length() const
    {
        return this->m_length;
    }

    long
    PageTable::size() const
    {
        return this->m_size;
    }

    long
    PageTable::page() const
    {
        return this->m_page;
    }

    bool
    PageTable::isFull() const
    {
        long length =
            this->m_size * sizeof(Item);

        return this->m_length == length;
    }

    bool
    PageTable::isEmpty() const
    {
        return this->m_size == 0;
    }

    bool
    PageTable::insert(const Page& page, word offset)
    {
        if ( this->isFull() ) return false;

        if ( page.length() != this->m_page )
            return false;

        if ( page.isNull() == false ) {
            this->m_memory[this->m_size] = {
                .memory = page.memory(),
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

        if ( this->isEmpty() ) return {};

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
