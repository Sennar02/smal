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
        this->resize(size);
    }

    template <class Type>
    PagedArray<Type>::PagedArray(BaseOrigin* origin, PageTable& ptable, usize size)
        : PageTable(move(ptable))
        , m_origin {origin}
    {
        this->resize(size);
    }

    template <class Type>
    PagedArray<Type>::~PagedArray()
    {
        this->resize(0);
    }

    template <class Type>
    usize
    PagedArray<Type>::size() const
    {
        usize ratio =
            Math::floor(this->m_page, SIZE);

        return ratio * this->m_count;
    }

    template <class Type>
    bool
    PagedArray<Type>::resize(usize size)
    {
        usize ratio = Math::floor(this->m_page, SIZE);
        usize pages = Math::ceil(size, ratio);

        if ( pages > this->m_count )
            return this->attach(pages - this->m_count);

        return this->detach(this->m_count - pages);
    }

    template <class Type>
    bool
    PagedArray<Type>::attach(usize pages)
    {
        usize delta = this->m_count + pages;
        usize count = 0;

        if ( delta > this->m_size )
            return false;

        for ( usize k = this->m_count; k < delta; k++ ) {
            auto page = this->m_origin->reserve(0);

            if ( this->insert(k, page) == false )
                this->m_origin->reclaim(page), k = delta;
            else
                count++;
        }

        return count == pages;
    }

    template <class Type>
    bool
    PagedArray<Type>::detach(usize pages)
    {
        usize delta = this->m_count - pages;

        if ( delta > this->m_count )
            return false;

        for ( usize k = this->m_count; k > delta; k-- ) {
            auto* item = this->remove(k - 1);
            Page  page = {this->m_origin, item, this->m_page};

            if ( this->m_origin->reclaim(page) == false )
                return false;
        }

        return true;
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
        return (Type&) *this->lookup(index * SIZE);
    }

    template <class Type>
    const Type&
    PagedArray<Type>::operator[](usize index) const
    {
        return (Type&) *this->lookup(index * SIZE);
    }
} // namespace ma
