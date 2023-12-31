#ifndef SMAL_MEMORY_ORIGIN_STACK_ORIGIN_HPP
#define SMAL_MEMORY_ORIGIN_STACK_ORIGIN_HPP

#include <smal/Memory/Origin/ArenaOrigin.hpp>

namespace ma
{
    class StackOrigin
        : public ArenaOrigin
    {
    public:
        /**
         *
         */
        StackOrigin();

        /**
         *
         */
        StackOrigin(void* memory, u32 size);

        /**
         *
         */
        virtual bool
        availab(u32 size) const;

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
    };
} // namespace ma

#endif // SMAL_MEMORY_ORIGIN_STACK_ORIGIN_HPP
