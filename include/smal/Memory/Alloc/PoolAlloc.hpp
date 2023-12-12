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
        PoolAlloc(void* memory, u32 size, u32 page = 0);

        /**
         *
         */
        virtual u32
        page() const;

        /**
         *
         */
        virtual u32
        count() const;

        /**
         *
         */
        virtual u32
        size() const;

        /**
         *
         */
        virtual u32
        next() const;

        /**
         *
         */
        virtual char*
        memory() const;

        /**
         *
         */
        virtual bool
        contains(void* memory) const;

        /**
         *
         */
        virtual bool
        prepare(u32 page);

        /**
         *
         */
        virtual bool
        prepare();

        /**
         *
         */
        virtual char*
        acquire(u32 size);

        /**
         *
         */
        virtual char*
        acquire();

        /**
         *
         */
        virtual bool
        release(void* memory);

    private:
        struct Node
        {
            Node* next;
        };

        struct Head
        {
            u32 used;
        };

        /**
         *
         */
        static const u32 s_node_size =
            sizeof(Node);

        /**
         *
         */
        static const u32 s_head_size =
            sizeof(Head);

    private:
        /**
         *
         */
        char* m_memory;

        /**
         *
         */
        u32 m_size;

        /**
         *
         */
        u32 m_count;

        /**
         *
         */
        Node* m_list;

        /**
         *
         */
        u32 m_page;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_POOL_ALLOC_HPP
