#ifndef SMAL_MEMORY_ALLOC_ARENA_ALLOC_HPP
#define SMAL_MEMORY_ALLOC_ARENA_ALLOC_HPP

#include <smal/Memory/Alloc/BaseAlloc.hpp>

namespace ma
{
    class ArenaAlloc
        : public BaseAlloc
    {
    public:
        /**
         *
         */
        ArenaAlloc();

        /**
         *
         */
        ArenaAlloc(void* memory, u32 size);

        /**
         *
         */
        virtual u32
        size() const;

        /**
         *
         */
        virtual char*
        memory();

        /**
         *
         */
        virtual const char*
        memory() const;

        /**
         *
         */
        virtual bool
        contains(void* memory) const;

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

#endif // SMAL_MEMORY_ALLOC_ARENA_ALLOC_HPP
