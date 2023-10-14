#ifndef SMAL_MEMORY_PAGE_ALLOC_HPP
#define SMAL_MEMORY_PAGE_ALLOC_HPP

#include <smal/Memory/Part.hpp>

namespace smal
{
    class PageAlloc
    {
    public:
        /**
         * @brief
         */
        PageAlloc();

        /**
         * @brief
         *
         * @param memory
         * @param length
         * @param page
         */
        PageAlloc(void* memory, usize length, usize page);

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
        prepare();

        /**
         * @brief
         *
         * @param page
         *
         * @return true
         * @return false
         */
        bool
        prepare(usize page);

        /**
         * @brief
         *
         * @return Part
         */
        Part
        reserve();

        /**
         * @brief
         *
         * @param page
         *
         * @return true
         * @return false
         */
        bool
        reclaim(const Part& page);

    private:
        struct Node
        {
            Node* next;
        };

        /**
         * @brief
         */
        char* m_memory;

        /**
         * @brief
         */
        usize m_length;

        /**
         * @brief
         */
        Node* m_list;

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

#endif // SMAL_MEMORY_PAGE_ALLOC_HPP
