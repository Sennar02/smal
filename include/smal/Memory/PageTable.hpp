#ifndef SMAL_MEMORY_PAGE_TABLE_HPP
#define SMAL_MEMORY_PAGE_TABLE_HPP

#include <smal/Memory/Page.hpp>

namespace ma
{
    class PageTable
    {
    public:
        /**
         * Creates an empty page table.
         */
        PageTable();

        /**
         * Creates a page table using a memory page as its
         * memory buffer.
         *
         * Every page associated inside the table is and must
         * be of the same size as this page.
         *
         * @param page Memory page.
         */
        PageTable(const Page& page);

        /**
         * Creates a page table from a memory buffer of a specified
         * size.
         *
         * Every page associated inside the table is and must be
         * of the specified size.
         *
         * @param memory Pointer to memory.
         * @param size   Size of the table in bytes.
         * @param page   Size of each page in bytes.
         */
        PageTable(void* memory, usize size, usize page);

        /**
         * @return The maximum number of entries.
         */
        usize
        size() const;

        /**
         * @return The current number of entries.
         */
        usize
        count() const;

        /**
         * @return The size of each page.
         */
        usize
        page() const;

        /**
         * Verifies if the table is empty.
         *
         * This operation is equal to:
         *
         * ```
         * table.count() == 0
         * ```
         *
         * @return True if it's empty.
         * @return False otherwise.
         */
        bool
        is_empty() const;

        /**
         * Verifies if the table is full.
         *
         * This operation is equal to:
         *
         * ```
         * table.count() == table.size()
         * ```
         *
         * @return True if it's full.
         * @return False otherwise.
         */
        bool
        is_full() const;

        /**
         * Associates a memory page to a particular key for
         * future lookups.
         *
         * The page is always left intact.
         *
         * This function fails in any of the following cases:
         * - The table is full
         * - The page is null
         * - The page is of a different size than required
         * - The key is beyond the size of the table
         * - The key is already associated to a page
         *
         * @param key  Key to associate.
         * @param page Memory page to associate.
         *
         * @return True if the page is successfully associated.
         * @return False otherwise.
         */
        bool
        insert(usize key, const Page& page);

        /**
         * Removes the association of a particular key.
         *
         * The value of the association is returned as
         * the output of the function, if it fails such
         * value is null.
         *
         * This funcion fails in any of the following cases:
         * - The table is empty
         * - The key is beyond the size of the table
         * - The key is not associated to a page
         *
         * @param key Key to disassociate
         *
         * @return The association, or null.
         */
        char*
        remove(usize key);

        /**
         * Translates a virtual index to the corresponding
         * real address.
         *
         * @param index Virtual index to translate.
         *
         * @return The corresponding address.
         */
        char*
        lookup(usize index) const;

    public:
        using Node = char*;

        /**
         * Pointer to memory.
         */
        Node* m_memory;

        /**
         * Size of the table in entries.
         */
        usize m_size;

        /**
         * Number of current associations.
         */
        usize m_count;

        /**
         * Size of each page in bytes.
         */
        usize m_page;
    };
} // namespace ma

#endif // SMAL_MEMORY_PAGE_TABLE_HPP
