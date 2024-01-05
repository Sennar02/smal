#ifndef SMAL_MEMORY_BUFFER_PAGED_BUFFER_HPP
#define SMAL_MEMORY_BUFFER_PAGED_BUFFER_HPP

#include <smal/Memory/Buffer/BaseBuffer.hpp>
#include <smal/Memory/Origin/PoolOrigin.hpp>
#include <smal/Memory/Origin/DummyOrigin.hpp>
#include <smal/Memory/MemoryTable.hpp>

namespace ma
{
    template <class Item>
    class PagedBuffer
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
        PagedBuffer(u32 size = 0, u32 page = 0);

        /**
         *
         */
        PagedBuffer(BaseOrigin& origin, u32 size, u32 page, const Item& item);

        /**
         *
         */
        PagedBuffer(BaseOrigin& origin, u32 size, u32 page);

        /**
         *
         */
        PagedBuffer(PoolOrigin& origin, u32 size, const Item& item);

        /**
         *
         */
        PagedBuffer(PoolOrigin& origin, u32 size);

        /**
         *
         */
        PagedBuffer(MemoryTable&& memory, u32 page, BaseOrigin* origin = 0);

        /**
         *
         */
        virtual const MemoryTable&
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
        virtual Item*
        search(u32 index) const;

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

    private:
        /**
         *
         */
        bool
        expand(u32 pages);

        /**
         *
         */
        bool
        shrink(u32 pages);

        /**
         *
         */
        u32
        toItems(u32 pages) const;

        /**
         *
         */
        u32
        toPages(u32 items) const;

    private:
        /**
         *
         */
        MemoryTable m_memory;

        /**
         *
         */
        BaseOrigin* m_origin;

        /**
         *
         */
        u32 m_page;
    };
} // namespace ma

#include <smal/Memory/inline/Buffer/PagedBuffer.inl>

#endif // SMAL_MEMORY_BUFFER_PAGED_BUFFER_HPP
