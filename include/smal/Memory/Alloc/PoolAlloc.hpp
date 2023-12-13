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
        PoolAlloc(void* memory, u32 size, u32 page);

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
        virtual bool
        availab(u32 size) const;

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
        struct Node;
        union Head;

        /**
         *
         */
        static const u32 s_node_size;

        /**
         *
         */
        static const u32 s_head_size;

    private:
        /**
         *
         */
        Node* m_list;

        /**
         *
         */
        u32 m_page;

        /**
         *
         */
        u32 m_count;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_POOL_ALLOC_HPP
