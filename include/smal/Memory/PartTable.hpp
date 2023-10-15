#ifndef SMAL_MEMORY_PART_TABLE_HPP
#define SMAL_MEMORY_PART_TABLE_HPP

#include <smal/Memory/Part.hpp>

namespace smal
{
    class PartTable
    {
    public:
        /**
         * @brief
         */
        PartTable();

        /**
         * @brief
         *
         * @param memory
         * @param length
         * @param page
         */
        PartTable(void* memory, usize length, usize page);

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
         * @param index
         *
         * @return true
         * @return false
         */
        bool
        insert(const Part& page, usize index);

        /**
         * @brief
         *
         * @param index
         *
         * @return char*
         */
        char*
        remove(usize index);

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
        /**
         * @brief
         */
        char** m_memory;

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

#endif // SMAL_MEMORY_PART_TABLE_HPP
