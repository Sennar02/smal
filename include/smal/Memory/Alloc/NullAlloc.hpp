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
        NullAlloc(void* memory, usize size);

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
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_NULL_ALLOC_HPP
