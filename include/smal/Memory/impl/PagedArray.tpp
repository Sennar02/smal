#include <smal/Memory/Array/PagedArray.hpp>

namespace ma
{
    template <class Type>
    PagedArray<Type>::PagedArray()
        : PageTable()
        , m_origin {0}
    { }

    template <class Type>
    PagedArray<Type>::PagedArray(BaseOrigin* origin, usize length)
        : PageTable(origin->reserve(0))
        , m_origin {origin}
    {
        this->resize(length);
    }

    template <class Type>
    PagedArray<Type>::PagedArray(BaseOrigin* origin, PageTable& ptable, usize length)
        : PageTable(move(ptable))
        , m_origin {origin}
    {
        this->resize(length);
    }

    template <class Type>
    PagedArray<Type>::~PagedArray()
    {
        this->resize(0);
    }

    template <class Type>
    usize
    PagedArray<Type>::length() const
    {
        usize ratio =
            Math::floor(this->m_page, SIZE);

        return ratio * this->m_size;
    }

    template <class Type>
    bool
    PagedArray<Type>::resize(usize length)
    {
        usize ratio = Math::floor(this->m_page, SIZE);
        usize pages = Math::ceil(length, ratio);

        if ( pages > this->m_size )
            return this->attach(pages - this->m_size);

        return this->detach(this->m_size - pages);
    }

    template <class Type>
    bool
    PagedArray<Type>::attach(usize pages)
    {
        usize delta = this->m_size + pages;
        usize count = 0;

        if ( delta > this->m_length )
            return false;

        for ( usize k = this->m_size; k < delta; k++ ) {
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
        usize delta = this->m_size - pages;

        if ( delta > this->m_size )
            return false;

        for ( usize k = this->m_size; k > delta; k-- ) {
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
