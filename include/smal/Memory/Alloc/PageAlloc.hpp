#ifndef SMAL_MEMORY_ALLOC_PAGE_ALLOC_HPP
#define SMAL_MEMORY_ALLOC_PAGE_ALLOC_HPP

#include <smal/Memory/Alloc/BaseAlloc.hpp>

namespace ma
{
    class PageAlloc
        : public BaseAlloc
    {
    public:
        /**
         *
         */
        PageAlloc();

        /**
         *
         */
        PageAlloc(void* memory, usize size, usize page = 0);

        /**
         *
         */
        usize
        page() const;

        /**
         *
         */
        usize
        avail() const;

        /**
         *
         */
        bool
        prepare();

        /**
         *
         */
        bool
        prepare(usize page);

        /**
         *
         */
        char*
        acquire(usize size = 0);

        /**
         *
         */
        bool
        release(void* memory);

        /**
         *
         */
        bool
        release();

    private:
        struct Node
        {
            Node* next;
        };

    private:
        /**
         *
         */
        Node* m_list;

        /**
         *
         */
        usize m_page;

        /**
         *
         */
        usize m_count;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_PAGE_ALLOC_HPP
