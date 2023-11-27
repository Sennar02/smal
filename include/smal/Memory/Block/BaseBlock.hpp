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
        virtual usize
        size() const = 0;

        /**
         *
         */
        virtual bool
        resize(usize size) = 0;

        /**
         *
         */
        virtual Type&
        operator[](usize index) = 0;

        /**
         *
         */
        virtual const Type&
        operator[](usize index) const = 0;
    };
} // namespace ma

#endif // SMAL_MEMORY_BLOCK_BASE_BLOCK_HPP
