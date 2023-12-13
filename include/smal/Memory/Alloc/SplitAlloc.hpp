#ifndef SMAL_MEMORY_ALLOC_SPLIT_ALLOC_HPP
#define SMAL_MEMORY_ALLOC_SPLIT_ALLOC_HPP

#include <smal/Memory/Alloc/BaseAlloc.hpp>

namespace ma
{
    class SplitAlloc
        : public BaseAlloc
    {
    public:
        /**
         *
         */
        SplitAlloc();

        /**
         *
         */
        SplitAlloc(void* memory, u32 size, u32 unit);

        /**
         *
         */
        virtual u32
        unit() const;

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
        union Head;

        /**
         *
         */
        static const u32 s_head_size;

    private:
        /**
         *
         */
        void*
        split(void* memory, u32 size) const;

        /**
         *
         */
        void*
        merge(void* memory) const;

        /**
         *
         */
        void*
        search(u32 size) const;

    private:
        /**
         *
         */
        char* m_memory;

        /**
         *
         */
        u32 m_size;

        /**
         *
         */
        u32 m_unit;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_SPLIT_ALLOC_HPP
