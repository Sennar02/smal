#include <smal/Memory/Array/PagedArray.hpp>

namespace smal
{
    template <class Type>
    PagedArray<Type>::PagedArray()
        : m_origin {0}
        , m_table {}
    { }

    template <class Type>
    PagedArray<Type>::PagedArray(BaseOrigin* origin, usize length)
        : m_origin {origin}
        , m_table {}
    {
        Part page = origin->reserve(0);

        if ( page.isNull() == false ) {
            create(this->m_table,
                page.memory(),
                page.length(),
                page.length());

            this->resize(length);
        }
    }

    template <class Type>
    PagedArray<Type>::PagedArray(BaseOrigin* origin, PartTable& table, usize length)
        : m_origin {origin}
        , m_table {move(table)}
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
        usize page = this->m_table.page();
        usize size = this->m_table.size();

        usize fact = Math::floor(page, SIZE); // items per page.

        return fact * size;
    }

    template <class Type>
    bool
    PagedArray<Type>::resize(usize length)
    {
        usize page = this->m_table.page();
        usize size = this->m_table.size();

        usize fact = Math::floor(page, SIZE); // items per page.
        usize numb = Math::ceil(length, fact);

        if ( numb > size )
            return this->attach(numb - size);
        else
            return this->detach(size - numb);
    }

    template <class Type>
    bool
    PagedArray<Type>::attach(usize pages)
    {
        usize start = this->m_table.size();
        isize delta = start + pages;

        for ( isize i = start; i < delta; i++ ) {
            Part page = this->m_origin->reserve(0);

            if ( this->m_table.insert(page, i) == false ) {
                this->m_origin->reclaim(page);

                return false;
            }
        }

        return true;
    }

    template <class Type>
    bool
    PagedArray<Type>::detach(usize pages)
    {
        isize start = this->m_table.size();
        isize delta = start - pages;

        for ( isize i = start - 1; i >= delta; i-- ) {
            Part page = {
                this->m_origin,
                this->m_table.remove(i),
                this->m_table.page(),
            };

            if ( this->m_origin->reclaim(page) == false )
                return false;
        }

        return true;
    }

    template <class Type>
    Type&
    PagedArray<Type>::operator[](usize index)
    {
        auto item =
            this->m_table.lookup(index, SIZE);

        return *(Type*) item;
    }

    template <class Type>
    const Type&
    PagedArray<Type>::operator[](usize index) const
    {
        auto item =
            this->m_table.lookup(index, SIZE);

        return *(const Type*) item;
    }
} // namespace smal
