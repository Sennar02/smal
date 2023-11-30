#ifndef SMAL_MEMORY_ALLOC_POOL_ALLOC_HPP
#define SMAL_MEMORY_ALLOC_POOL_ALLOC_HPP

#include <smal/Memory/Alloc/BaseAlloc.hpp>

namespace ma
{
    class PoolAlloc
        : public BaseAlloc
    {
    public:
        /**
         *
         */
        PoolAlloc();

        /**
         *
         */
        PoolAlloc(void* memory, usize size, usize page = 0);

        /**
         *
         */
        usize
        page() const;

        /**
         *
         */
        virtual usize
        avail() const;

        /**
         *
         */
        virtual bool
        prepare(usize page);

        /**
         *
         */
        virtual bool
        prepare();

        /**
         *
         */
        virtual char*
        acquire(usize size = g_max_usize);

        /**
         *
         */
        virtual bool
        release(void* memory);

        /**
         *
         */
        virtual bool
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

#endif // SMAL_MEMORY_ALLOC_POOL_ALLOC_HPP
