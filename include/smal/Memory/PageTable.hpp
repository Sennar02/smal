#ifndef SMAL_MEMORY_PAGE_TABLE_HPP
#define SMAL_MEMORY_PAGE_TABLE_HPP

#include <smal/Memory/depend.hpp>
#include <smal/Memory/Page.hpp>

namespace smal
{
    class PageTable
    {
    public:
        /**
         * @brief
         */
        PageTable();

        /**
         * @brief
         *
         * @param memory
         * @param length
         */
        PageTable(void* memory, long length);

        /**
         * @brief
         *
         * @param page
         * @param offset
         *
         * @return true
         * @return false
         */
        bool
        insert(Page& page, long offset);

        /**
         * @brief
         *
         * @param page
         *
         * @return true
         * @return false
         */
        bool
        remove(Page& page);

        /**
         * @brief
         *
         * @param index
         *
         * @return Tuple<char*, long>
         */
        Tuple<char*, long>
        lookup(long index);

    private:
        /**
         * @brief
         *
         * @param page
         *
         * @return long
         */
        long
        search(Page& page);

    public:
        struct Entry
        {
            char* memory;
            long  length;
            long  offset;
        };

        /**
         * @brief
         */
        Entry* m_memory;

        /**
         * @brief
         */
        long m_length;

        /**
         * @brief
         */
        long m_size;
    };
} // namespace smal

#endif // SMAL_MEMORY_PAGE_TABLE_HPP
