#ifndef SMAL_MEMORY_ARRAY_HPP
#define SMAL_MEMORY_ARRAY_HPP

#include <smal/Memory/define.hpp>

namespace ma
{
    template <class Item, class Layout = FixedLayout>
    class Array
        : public Layout
    {
    public:
        /**
         *
         */
        static const u32 s_size = sizeof(Item);

    public:
        /**
         *
         */
        template <class Origin, class... Args>
        Array(Origin& origin, u32 length, Args&&... args);

        /**
         *
         */
        Array(const Layout& layout);

        /**
         *
         */
        u32
        length() const;

        /**
         *
         */
        bool
        resize(u32 length);

        /**
         *
         */
        Item&
        find(u32 index) const;

        /**
         *
         */
        Item&
        operator[](u32 index) const;
    };
} // namespace ma

#include <smal/Memory/inline/Array.inl>

#endif // SMAL_MEMORY_ARRAY_HPP
