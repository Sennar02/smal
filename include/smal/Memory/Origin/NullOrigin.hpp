#ifndef SMAL_MEMORY_ORIGIN_NULL_ORIGIN_HPP
#define SMAL_MEMORY_ORIGIN_NULL_ORIGIN_HPP

#include <smal/Memory/Origin/BaseOrigin.hpp>

namespace ma
{
    class NullOrigin
        : public BaseOrigin
    {
    public:
        /**
         *
         */
        NullOrigin();

        /**
         *
         */
        NullOrigin(const SimpleBuffer<char>& buffer);

        /**
         *
         */
        NullOrigin(void* memory, u32 size);

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
    };
} // namespace ma

#endif // SMAL_MEMORY_ORIGIN_NULL_ORIGIN_HPP
