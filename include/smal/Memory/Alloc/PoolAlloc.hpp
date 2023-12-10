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
        size() const;

        /**
         *
         */
        virtual u32
        avail() const;

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
        acquire(u32 size = g_max_u32);

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

        /**
         *
         */
        static const u32 s_node_size =
            sizeof(Node);

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
