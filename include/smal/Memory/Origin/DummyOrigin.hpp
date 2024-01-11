#ifndef SMAL_MEMORY_ORIGIN_SYSTEM_ORIGIN_HPP
#define SMAL_MEMORY_ORIGIN_SYSTEM_ORIGIN_HPP

#include <smal/Memory/Origin/BaseOrigin.hpp>

namespace ma
{
    class DummyOrigin
        : public BaseOrigin
    {
    public:
        /**
         *
         */
        DummyOrigin();

        /**
         *
         */
        DummyOrigin(void* memory, u32 size);

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
    };
} // namespace ma

#endif // SMAL_MEMORY_ORIGIN_SYSTEM_ORIGIN_HPP
