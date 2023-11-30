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
        BaseAlloc(void* memory, u32 size);

        /**
         *
         */
        virtual ~BaseAlloc() = default;

        /**
         *
         */
        u32
        size() const;

        /**
         *
         */
        char*
        memory();

        /**
         *
         */
        const char*
        memory() const;

        /**
         *
         */
        virtual bool
        contains(void* memory);

        /**
         *
         */
        virtual u32
        avail() const = 0;

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

        /**
         *
         */
        virtual bool
        release() = 0;

    protected:
        /**
         *
         */
        char* m_memory;

        /**
         *
         */
        u32 m_size;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_BASE_ALLOC_HPP
