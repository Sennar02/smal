#ifndef SMAL_MEMORY_ALLOC_STACK_ALLOC_HPP
#define SMAL_MEMORY_ALLOC_STACK_ALLOC_HPP

#include <smal/Memory/Alloc/BaseAlloc.hpp>

namespace ma
{
    class StackAlloc
        : public BaseAlloc
    {
    public:
        /**
         *
         */
        StackAlloc();

        /**
         *
         */
        StackAlloc(void* memory, usize size);

        /**
         *
         */
        virtual usize
        avail() const;

        /**
         *
         */
        virtual bool
        prepare();

        /**
         *
         */
        virtual char*
        acquire(usize size);

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
        struct Head
        {
            usize size;
        };

        /**
         *
         */
        static const usize s_head_size =
            sizeof(Head);

    private:
        /**
         *
         */
        char* m_cursor;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_STACK_ALLOC_HPP
