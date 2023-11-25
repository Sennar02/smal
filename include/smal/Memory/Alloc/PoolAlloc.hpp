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
        release(char* addr);

    private:
        struct Node
        {
            Node* next;
        };

        /**
         *
         */
        Node* m_list;

        /**
         *
         */
        usize m_page;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_POOL_ALLOC_HPP
