#ifndef SMAL_MEMORY_BLOCK_BASE_BLOCK_HPP
#define SMAL_MEMORY_BLOCK_BASE_BLOCK_HPP

#include <smal/Memory/define.hpp>

namespace ma
{
    template <class Type>
    class BaseBlock
    {
    public:
        /**
         *
         */
        virtual ~BaseBlock() = default;

        /**
         *
         */
        virtual u32
        size() const = 0;

        /**
         *
         */
        virtual bool
        resize(u32 size) = 0;

        /**
         *
         */
        virtual Type&
        operator[](u32 index) = 0;

        /**
         *
         */
        virtual const Type&
        operator[](u32 index) const = 0;
    };
} // namespace ma

#endif // SMAL_MEMORY_BLOCK_BASE_BLOCK_HPP
