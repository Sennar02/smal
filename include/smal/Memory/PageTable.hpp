#ifndef SMAL_MEMORY_PAGE_TABLE_HPP
#define SMAL_MEMORY_PAGE_TABLE_HPP

#include <smal/Memory/Part.hpp>

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
        PageTable(void* memory, usize length, usize page);

        /**
         * @brief
         *
         * @return usize
         */
        usize
        length() const;

        /**
         * @brief
         *
         * @return usize
         */
        usize
        size() const;

        /**
         * @brief
         *
         * @return usize
         */
        usize
        page() const;

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool
        isFull() const;

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool
        isEmpty() const;

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
        insert(const Part& page, usize offset);

        /**
         * @brief
         *
         * @param offset
         *
         * @return char*
         */
        char*
        remove(usize offset);

        /**
         * @brief
         *
         * @param index
         * @param scale
         *
         * @return char*
         */
        char*
        lookup(usize index, usize scale = 1) const;

    public:
        using Item = char*;

        /**
         * @brief
         */
        Item* m_memory;

        /**
         * @brief
         */
        usize m_length;

        /**
         * @brief
         */
        usize m_size;

        /**
         * @brief
         */
        usize m_page;
    };
} // namespace smal

#endif // SMAL_MEMORY_PAGE_TABLE_HPP
