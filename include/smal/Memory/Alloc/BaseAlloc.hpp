#ifndef SMAL_MEMORY_ALLOC_BASE_ALLOC_HPP
#define SMAL_MEMORY_ALLOC_BASE_ALLOC_HPP

#include <smal/Memory/define.hpp>

namespace ma
{
    class BaseAlloc
    {
    public:
        /**
         *
         */
        virtual ~BaseAlloc() = default;

        /**
         *
         */
        virtual u32
        size() const = 0;

        /**
         *
         */
        virtual u32
        avail() const = 0;

        /**
         *
         */
        virtual char*
        memory() const = 0;

        /**
         *
         */
        virtual bool
        contains(void* memory) const = 0;

        /**
         *
         */
        virtual bool
        prepare() = 0;

        /**
         *
         */
        virtual char*
        acquire(u32 size) = 0;

        /**
         *
         */
        virtual bool
        release(void* memory) = 0;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_BASE_ALLOC_HPP
