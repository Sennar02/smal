#ifndef SMAL_MEMORY_PAGE_ALLOC_HPP
#define SMAL_MEMORY_PAGE_ALLOC_HPP

#include <smal/Memory/Page.hpp>

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
        PageAlloc(void* memory, long length, long page);

        /**
         * @brief
         *
         * @return long
         */
        long
        length() const;

        /**
         * @brief
         *
         * @return long
         */
        long
        size() const;

        /**
         * @brief
         *
         * @return long
         */
        long
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
        prepare(long page);

        /**
         * @brief
         *
         * @return Page
         */
        Page
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
        reclaim(const Page& page);

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
        long m_length;

        /**
         * @brief
         */
        Node* m_list;

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

#endif // SMAL_MEMORY_PAGE_ALLOC_HPP
