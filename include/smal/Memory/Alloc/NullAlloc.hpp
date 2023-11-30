#ifndef SMAL_MEMORY_ALLOC_NULL_ALLOC_HPP
#define SMAL_MEMORY_ALLOC_NULL_ALLOC_HPP

#include <smal/Memory/Alloc/BaseAlloc.hpp>

namespace ma
{
    class NullAlloc
        : public BaseAlloc
    {
    public:
        /**
         *
         */
        NullAlloc();

        /**
         *
         */
        NullAlloc(void* memory, u32 size);

        /**
         *
         */
        virtual u32
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
        acquire(u32 size);

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
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_NULL_ALLOC_HPP
