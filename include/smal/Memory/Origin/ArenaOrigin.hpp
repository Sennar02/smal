#ifndef SMAL_MEMORY_ORIGIN_ARENA_ORIGIN_HPP
#define SMAL_MEMORY_ORIGIN_ARENA_ORIGIN_HPP

#include <smal/Memory/Origin/BaseOrigin.hpp>

namespace ma
{
    class ArenaOrigin
        : public BaseOrigin
    {
    public:
        /**
         *
         */
        ArenaOrigin();

        /**
         *
         */
        ArenaOrigin(const SimpleBuffer<char>& buffer);

        /**
         *
         */
        ArenaOrigin(void* memory, u32 size);

        /**
         *
         */
        virtual bool
        remains(u32 size) const;

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

    protected:
        /**
         *
         */
        char* m_pntr;
    };
} // namespace ma

#endif // SMAL_MEMORY_ORIGIN_ARENA_ORIGIN_HPP
