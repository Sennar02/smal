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
        usize
        avail() const;

        /**
         *
         */
        bool
        prepare();

        /**
         *
         */
        char*
        acquire(usize size);

        /**
         *
         */
        bool
        release(void* memory);

        /**
         *
         */
        bool
        release();
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_NULL_ALLOC_HPP
