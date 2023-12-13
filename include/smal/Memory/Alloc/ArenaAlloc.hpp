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
        /**
         *
         */
        char* m_cursor;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_ARENA_ALLOC_HPP
