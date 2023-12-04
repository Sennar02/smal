#include <smal/Memory/Block/PagedBlock.hpp>

namespace ma
{
    template <class Type>
    PagedBlock<Type>::PagedBlock()
        : m_alloc {0}
        , m_table {}
    { }

    template <class Type>
    PagedBlock<Type>::PagedBlock(PoolAlloc& alloc, u32 size)
        : m_alloc {&alloc}
        , m_table {}
    {
        u32   page = m_alloc->page();
        char* addr = m_alloc->acquire(page);

        if ( addr != 0 )
            m_table = {addr, page, page};

        resize(size);
    }

    template <class Type>
    PagedBlock<Type>::PagedBlock(PoolAlloc& alloc, const PageTable& table)
        : m_alloc {&alloc}
        , m_table {table}
    { }

    template <class Type>
    u32
    PagedBlock<Type>::size() const
    {
        u32 pages = m_table.count();
        u32 items = m_alloc->page() / s_type_size;

        return pages * items;
    }

    template <class Type>
    bool
    PagedBlock<Type>::resize(u32 size)
    {
        u32 pages = m_table.count();
        u32 items = m_alloc->page() / s_type_size;

        if ( items != 0 ) {
            size = ceil(size, items);

            if ( pages == size ) return true;

            if ( pages < size )
                return expand(size - pages);
            else
                return shrink(pages - size);
        }

        return false;
    }

    template <class Type>
    bool
    PagedBlock<Type>::expand(u32 pages)
    {
        u32   page = m_alloc->page();
        char* addr = 0;

        if ( m_table.count() + pages > m_table.size() )
            return false;

        if ( m_alloc->avail() / page < pages )
            return false;

        for ( u32 i = 0; i < pages; i++ ) {
            addr = m_alloc->acquire(page);

            if ( addr != 0 )
                m_table.push(addr);
            else
                return false;
        }

        return true;
    }

    template <class Type>
    bool
    PagedBlock<Type>::shrink(u32 pages)
    {
        char* addr = 0;

        if ( m_table.count() - pages < 0 )
            return false;

        for ( u32 i = 0; i < pages; i++ ) {
            addr = m_table.pull();

            if ( addr != 0 )
                m_alloc->release(addr);
            else
                return false;
        }

        return true;
    }

    template <class Type>
    const PageTable&
    PagedBlock<Type>::table() const
    {
        return (PageTable&) *this;
    }

    template <class Type>
    Type&
    PagedBlock<Type>::operator[](u32 index)
    {
        char* addr =
            m_table.convert(index, s_type_size);

        return *(Type*) addr;
    }

    template <class Type>
    const Type&
    PagedBlock<Type>::operator[](u32 index) const
    {
        char* addr =
            m_table.convert(index, s_type_size);

        return *(Type*) addr;
    }
} // namespace ma
