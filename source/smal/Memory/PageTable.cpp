#include <smal/Memory/PageTable.hpp>
#include <smal/Memory/Origin/PoolOrigin.hpp>

namespace ma
{
    PageTable::PageTable()
        : m_memory {0}
        , m_size {0}
        , m_count {0}
        , m_page {0}
    { }

    PageTable::PageTable(const Page& page)
        : PageTable((char*) page.memory(), page.size(), page.size())
    { }

    PageTable::PageTable(void* memory, usize size, usize page)
        : m_memory {(Node*) memory}
        , m_size {size}
        , m_count {0}
        , m_page {page}
    {
        m_size /= sizeof(Node);
    }

    usize
    PageTable::size() const
    {
        return m_size;
    }

    usize
    PageTable::count() const
    {
        return m_count;
    }

    usize
    PageTable::page() const
    {
        return m_page;
    }

    bool
    PageTable::is_empty() const
    {
        return m_count == 0;
    }

    bool
    PageTable::is_full() const
    {
        return m_count == m_size;
    }

    bool
    PageTable::insert(usize key, const Page& page)
    {
        char* memory = (char*) page.memory();

        if ( m_size <= key ||
             m_page != page.size() )
            return false;

        if ( page.is_null() == false ) {
            if ( m_memory[key] != 0 )
                return false;

            m_count += 1;
            m_memory[key] = memory;

            return true;
        }

        return false;
    }

    char*
    PageTable::remove(usize key)
    {
        char* memory = 0;

        if ( key < m_size ) {
            if ( m_memory[key] != 0 ) {
                memory = m_memory[key];

                m_count -= 1;
                m_memory[key] = 0;
            }
        }

        return memory;
    }

    char*
    PageTable::lookup(usize index) const
    {
        usize page = Math::div(index, m_page);
        usize byte = Math::mod(index, m_page);

        return m_memory[page] + byte;
    }
} // namespace ma
