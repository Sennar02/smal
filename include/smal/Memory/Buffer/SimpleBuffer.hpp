#ifndef SMAL_MEMORY_BUFFER_SIMPLE_BUFFER_HPP
#define SMAL_MEMORY_BUFFER_SIMPLE_BUFFER_HPP

#include <smal/Memory/Buffer/BaseBuffer.hpp>

namespace ma
{
    template <class Item>
    class SimpleBuffer
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
        SimpleBuffer();

        /**
         *
         */
        template <class Type>
        SimpleBuffer(Type memory[], u32 size);

        /**
         *
         */
        template <class Origin>
        SimpleBuffer(Origin& origin, u32 size, const Item& item);

        /**
         *
         */
        template <class Origin>
        SimpleBuffer(Origin& origin, u32 size);

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

#include <smal/Memory/impl/Buffer/SimpleBuffer.tpp>

#endif // SMAL_MEMORY_BUFFER_SIMPLE_BUFFER_HPP