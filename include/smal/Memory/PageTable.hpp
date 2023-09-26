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
         * @param start
         *
         * @return true
         * @return false
         */
        bool
        insert(Page& page, long start);

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
        struct Record
        {
            char* memory;
            long  length;
            long  start;
        };

        /**
         * @brief
         */
        Record* m_memory;

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
