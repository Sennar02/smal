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
        BaseAlloc(void* memory, usize size);

        /**
         *
         */
        virtual ~BaseAlloc() = default;

        /**
         *
         */
        usize
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
        virtual usize
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
        acquire(usize size) = 0;

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
        usize m_size;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_BASE_ALLOC_HPP
