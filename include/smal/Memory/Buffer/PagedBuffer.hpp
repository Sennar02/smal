#ifndef SMAL_MEMORY_BUFFER_PAGED_BUFFER_HPP
#define SMAL_MEMORY_BUFFER_PAGED_BUFFER_HPP

#include <smal/Memory/Buffer/BaseBuffer.hpp>
#include <smal/Memory/Origin/PoolOrigin.hpp>

namespace ma
{
    template <class Item>
    class PagedBuffer
        : public BaseBuffer<Item>
    {
    public:
        static const u32 s_item_size;

    public:
        PagedBuffer();

        PagedBuffer(PoolOrigin& origin, u32 size);

        PagedBuffer(PoolOrigin& origin, u32 size, const Item& item);

        PagedBuffer(MemoryTable&& memory, PoolOrigin* origin = 0);

        virtual const MemoryTable&
        memory() const;

        virtual u32
        size() const;

        virtual bool
        resize(u32 size);

        virtual Item*
        search(u32 index) const;

        virtual Item&
        find(u32 index) const;

        virtual Item&
        operator[](u32 index) const;

    private:
        bool
        expand(u32 pages);

        bool
        shrink(u32 pages);

        // convert pages to items
        u32
        toItems(u32 pages) const;

        // convert items to pages
        u32
        toPages(u32 items) const;

    private:
        MemoryTable m_memory;

        PoolOrigin* m_origin;
    };
} // namespace ma

#include <smal/Memory/impl/Buffer/PagedBuffer.tpp>

#endif // SMAL_MEMORY_BUFFER_PAGED_BUFFER_HPP
