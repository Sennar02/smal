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
        StackAlloc(void* memory, u32 size);

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
        prepare();

        /**
         *
         */
        virtual char*
        acquire(u32 size);

        /**
         *
         */
        virtual bool
        release(void* memory);

    private:
        struct Head
        {
            u32 size;
        };

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
        char* m_cursor;

        /**
         *
         */
        u32 m_size;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_STACK_ALLOC_HPP
