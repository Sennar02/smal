#ifndef SMAL_MEMORY_BUFFER_BASE_BUFFER_HPP
#define SMAL_MEMORY_BUFFER_BASE_BUFFER_HPP

#include <smal/Memory/define.hpp>

namespace ma
{
    template <class Item>
    class BaseBuffer
    {
    public:
        /**
         *
         */
        virtual ~BaseBuffer() = default;

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
        virtual Item*
        search(u32 index) const = 0;

        /**
         *
         */
        virtual Item&
        find(u32 index) const = 0;

        /**
         *
         */
        virtual Item&
        operator[](u32 index) const = 0;
    };
} // namespace ma

#endif // SMAL_MEMORY_BUFFER_BASE_BUFFER_HPP
