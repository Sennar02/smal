#ifndef SMAL_MEMORY_ORIGIN_BASE_ORIGIN_HPP
#define SMAL_MEMORY_ORIGIN_BASE_ORIGIN_HPP

#include <smal/Memory/Buffer/FixedBuffer.hpp>

namespace ma
{
    class BaseOrigin
    {
    public:
        /**
         *
         */
        BaseOrigin();

        /**
         *
         */
        BaseOrigin(const FixedBuffer<char>& buffer);

        /**
         *
         */
        BaseOrigin(void* memory, u32 size);

        /**
         *
         */
        virtual ~BaseOrigin() = default;

        /**
         *
         */
        virtual const char*
        memory() const;

        /**
         *
         */
        virtual u32
        size() const;

        /**
         *
         */
        virtual bool
        contains(void* memory) const;

        /**
         *
         */
        virtual bool
        availab(u32 size) const = 0;

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

#endif // SMAL_MEMORY_ORIGIN_BASE_ORIGIN_HPP
