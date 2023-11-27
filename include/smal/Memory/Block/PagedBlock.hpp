#ifndef SMAL_MEMORY_BLOCK_PAGED_BLOCK_HPP
#define SMAL_MEMORY_BLOCK_PAGED_BLOCK_HPP

#include <smal/Memory/Alloc/PageTable.hpp>
#include <smal/Memory/Alloc/PageAlloc.hpp>

namespace ma
{
    template <class Type>
    class PagedBlock
    {
    public:
        /**
         *
         */
        PagedBlock();

        /**
         *
         */
        PagedBlock(PageAlloc& alloc, usize size = 0);

        /**
         *
         */
        PagedBlock(PageAlloc& alloc, PageTable& table);

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
        bool
        expand(usize pages);

        /**
         *
         */
        bool
        shrink(usize pages);

        /**
         *
         */
        void
        clear();

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

    private:
        /**
         *
         */
        PageAlloc* m_alloc;

        /**
         *
         */
        PageTable m_table;
    };
} // namespace ma

#include <smal/Memory/Block/impl/PagedBlock.tpp>

#endif // SMAL_MEMORY_BLOCK_PAGED_BLOCK_HPP
