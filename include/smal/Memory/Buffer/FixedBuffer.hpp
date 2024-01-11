#ifndef SMAL_MEMORY_BUFFER_SIMPLE_BUFFER_HPP
#define SMAL_MEMORY_BUFFER_SIMPLE_BUFFER_HPP

#include <smal/Memory/Buffer/BaseBuffer.hpp>

namespace ma
{
    template <class Item>
    class FixedBuffer
        : public BaseBuffer<Item>
    {
    public:
        /**
         *
         */
        static const u32 s_item_size;

    public:
        /**
         *
         */
        FixedBuffer(u32 size = 0);

        /**
         *
         */
        template <class Type>
        FixedBuffer(Type memory[], u32 size);

        /**
         *
         */
        FixedBuffer(BaseOrigin& origin, u32 size, const Item& item);

        /**
         *
         */
        FixedBuffer(BaseOrigin& origin, u32 size);

        /**
         *
         */
        virtual Item*
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
        resize(u32 size);

        /**
         *
         */
        virtual Item&
        find(u32 index) const;

        /**
         *
         */
        virtual Item&
        operator[](u32 index) const;

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

#include <smal/Memory/inline/Buffer/FixedBuffer.inl>

#endif // SMAL_MEMORY_BUFFER_SIMPLE_BUFFER_HPP
