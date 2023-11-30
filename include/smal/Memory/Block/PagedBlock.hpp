#ifndef SMAL_MEMORY_BLOCK_PAGED_BLOCK_HPP
#define SMAL_MEMORY_BLOCK_PAGED_BLOCK_HPP

#include <smal/Memory/Block/BaseBlock.hpp>
#include <smal/Memory/Block/PageTable.hpp>
#include <smal/Memory/Alloc/PoolAlloc.hpp>

namespace ma
{
    template <class Type>
    class PagedBlock
        : public BaseBlock<Type>
    {
    public:
        /**
         *
         */
        PagedBlock();

        /**
         *
         */
        PagedBlock(const PoolAlloc& alloc, u32 size);

        /**
         *
         */
        u32
        size() const;

        /**
         *
         */
        bool
        resize(u32 size);

        /**
         *
         */
        const PageTable&
        table() const;

        /**
         *
         */
        Type&
        operator[](u32 index);

        /**
         *
         */
        const Type&
        operator[](u32 index) const;

    private:
        /**
         *
         */
        static const u32 s_type_size
            = sizeof(Type);
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

    private:
        /**
         *
         */
        PoolAlloc m_alloc;

        /**
         *
         */
        PageTable m_table;
    };
} // namespace ma

#include <smal/Memory/Block/impl/PagedBlock.tpp>

#endif // SMAL_MEMORY_BLOCK_PAGED_BLOCK_HPP
