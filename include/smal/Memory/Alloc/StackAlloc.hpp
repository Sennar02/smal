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
        virtual bool
        availab(u32 size) const;

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
        union Head;

        /**
         *
         */
        static const u32 s_head_size;

    private:
        /**
         *
         */
        char* m_cursor;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_STACK_ALLOC_HPP
