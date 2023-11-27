#ifndef SMAL_MEMORY_ALLOC_AREA_ALLOC_HPP
#define SMAL_MEMORY_ALLOC_AREA_ALLOC_HPP

#include <smal/Memory/Alloc/BaseAlloc.hpp>

namespace ma
{
    class AreaAlloc
        : public BaseAlloc
    {
    public:
        /**
         *
         */
        AreaAlloc();

        /**
         *
         */
        AreaAlloc(void* memory, usize size);

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

    private:
        struct Head
        {
            usize size;
        };

        /**
         *
         */
        static const usize s_head_size =
            sizeof(Head);

    private:
        /**
         *
         */
        char* m_cursor;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_AREA_ALLOC_HPP
