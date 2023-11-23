#include <smal/Memory/Array/PagedArray.hpp>

namespace ma
{
    template <class Type>
    PagedArray<Type>::PagedArray()
        : PageTable()
        , m_origin {0}
    { }

    template <class Type>
    PagedArray<Type>::PagedArray(BaseOrigin* origin, usize size)
        : PageTable(origin->reserve(0))
        , m_origin {origin}
    {
        resize(size);
    }

    template <class Type>
    PagedArray<Type>::PagedArray(BaseOrigin* origin, PageTable& ptable, usize size)
        : PageTable(move(ptable))
        , m_origin {origin}
    {
        resize(size);
    }

    template <class Type>
    PagedArray<Type>::~PagedArray()
    {
        resize(0);
    }

    template <class Type>
    usize
    PagedArray<Type>::size() const
    {
        usize ratio =
            Math::floor(m_page, SIZE);

        return ratio * m_count;
    }

    template <class Type>
    bool
    PagedArray<Type>::resize(usize size)
    {
        usize ratio = Math::floor(m_page, SIZE);
        usize pages = Math::ceil(size, ratio);

        if ( pages > m_count )
            return attach(pages - m_count);

        return detach(m_count - pages);
    }

    template <class Type>
    bool
    PagedArray<Type>::attach(usize pages)
    {
        usize delta = m_count + pages;
        usize count = 0;

        if ( delta > m_size )
            return false;

        for ( usize k = m_count; k < delta; k++ ) {
            auto page = m_origin->reserve(0);

            if ( insert(k, page) == false )
                m_origin->reclaim(page), k = delta;
            else
                count++;
        }

        return count == pages;
    }

    template <class Type>
    bool
    PagedArray<Type>::detach(usize pages)
    {
        usize delta = m_count - pages;

        if ( delta > m_count )
            return false;

        for ( usize k = m_count; k > delta; k-- ) {
            auto* item = remove(k - 1);
            Page  page = {m_origin, item, m_page};

            if ( m_origin->reclaim(page) == false )
                return false;
        }

        return true;
    }

    template <class Type>
    void
    PagedArray<Type>::clear()
    {
        resize(0);
    }

    template <class Type>
    const PageTable&
    PagedArray<Type>::ptable() const
    {
        return *(PageTable*) this;
    }

    template <class Type>
    Type&
    PagedArray<Type>::operator[](usize index)
    {
        return *(Type*) lookup(index * SIZE);
    }

    template <class Type>
    const Type&
    PagedArray<Type>::operator[](usize index) const
    {
        return *(Type*) lookup(index * SIZE);
    }
} // namespace ma
