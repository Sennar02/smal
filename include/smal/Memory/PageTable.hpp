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
         * @param page
         */
        PageTable(void* memory, long length, long page);

        /**
         * @brief
         *
         * @return long
         */
        long
        get_length() const;

        /**
         * @brief
         *
         * @return long
         */
        long
        get_size() const;

        /**
         * @brief
         *
         * @return long
         */
        long
        get_page() const;

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool
        is_full() const;

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool
        is_empty() const;

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
        insert(const Page& page, word offset);

        /**
         * @brief
         *
         * @param index
         *
         * @return true
         * @return false
         */
        bool
        remove(long index = -1);

        /**
         * @brief
         *
         * @param index
         * @param scale
         *
         * @return char*
         */
        char*
        lookup(long index, long scale = 1) const;

    public:
        struct Item
        {
            char* memory;
            word  offset;
        };

        /**
         * @brief
         */
        Item* m_memory;

        /**
         * @brief
         */
        long m_length;

        /**
         * @brief
         */
        long m_size;

        /**
         * @brief
         */
        long m_page;
    };
} // namespace smal

#endif // SMAL_MEMORY_PAGE_TABLE_HPP
