#include <smal/Memory/Block/PagedBlock.hpp>

namespace ma
{
    template <class Type>
    PagedBlock<Type>::PagedBlock()
        : m_alloc {0}
        , m_table {}
    { }

    template <class Type>
    PagedBlock<Type>::PagedBlock(PageAlloc& alloc, usize size)
        : m_alloc {&alloc}
        , m_table {alloc.acquire(), alloc.page(), alloc.page()}
    {
        resize(size);
    }

    template <class Type>
    PagedBlock<Type>::PagedBlock(PageAlloc& alloc, PageTable& table)
        : m_alloc {&alloc}
        , m_table {table}
    { }

    template <class Type>
    PagedBlock<Type>::~PagedBlock()
    {
        clear();
    }

    template <class Type>
    usize
    PagedBlock<Type>::size() const
    {
        usize count = m_table.count();
        usize items = m_table.page() / s_type_size;

        return count * items;
    }

    template <class Type>
    bool
    PagedBlock<Type>::resize(usize size)
    {
        usize count = m_table.count();
        usize items = m_table.page() / s_type_size;

        if ( items != 0 ) {
            size = ceil(size, items);

            if ( count < size )
                return expand(size - count);
            else
                return shrink(count - size);
        }

        return false;
    }

    template <class Type>
    bool
    PagedBlock<Type>::expand(usize pages)
    {
        char* addr   = 0;
        bool  result = true;

        for ( usize i = 0; i < pages; i++ ) {
            addr   = m_alloc->acquire();
            result = m_table.insert(m_table.count(), addr);

            if ( result == false )
                m_alloc->release(addr), i = pages;
        }

        return result;
    }

    template <class Type>
    bool
    PagedBlock<Type>::shrink(usize pages)
    {
        char* addr   = 0;
        bool  result = true;

        for ( usize i = 0; i < pages; i++ ) {
            addr   = m_table.remove(m_table.count() - 1);
            result = m_alloc->release(addr);

            if ( result == false )
                i = pages;
        }

        return result;
    }

    template <class Type>
    void
    PagedBlock<Type>::clear()
    {
        shrink(m_table.count());
    }

    template <class Type>
    const PageTable&
    PagedBlock<Type>::table() const
    {
        return (PageTable&) *this;
    }

    template <class Type>
    Type&
    PagedBlock<Type>::operator[](usize index)
    {
        char* addr =
            m_table.convert(index, s_type_size);

        return *(Type*) addr;
    }

    template <class Type>
    const Type&
    PagedBlock<Type>::operator[](usize index) const
    {
        char* addr =
            m_table.convert(index, s_type_size);

        return *(Type*) addr;
    }
} // namespace ma
