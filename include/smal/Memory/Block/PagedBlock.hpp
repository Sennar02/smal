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
        PagedBlock(const PoolAlloc& alloc, usize size);

        /**
         *
         */
        virtual ~PagedBlock();

        /**
         *
         */
        usize
        size() const;

        /**
         *
         */
        bool
        resize(usize size);

        /**
         *
         */
        const PageTable&
        table() const;

        /**
         *
         */
        Type&
        operator[](usize index);

        /**
         *
         */
        const Type&
        operator[](usize index) const;

    private:
        /**
         *
         */
        static const usize s_type_size =
            sizeof(Type);
        /**
         *
         */
        bool
        expand(usize pages);

        /**
         *
         */
        bool
        shrink(usize pages);

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
