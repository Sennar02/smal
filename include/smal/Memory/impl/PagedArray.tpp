#include <smal/Memory/PagedArray.hpp>

namespace smal
{
    template <class Type>
    PagedArray<Type>::PagedArray()
        : m_table {}
        , m_origin {0}
    { }

    template <class Type>
    PagedArray<Type>::PagedArray(PageAlloc& origin, usize length)
        : m_table {}
        , m_origin {&origin}
    {
        Part page = origin.reserve();

        if ( page.isNull() == false ) {
            create(this->m_table,
                page.memory(),
                page.length(),
                page.length());

            this->resize(length);
        }
    }

    template <class Type>
    PagedArray<Type>::PagedArray(PageAlloc& origin, PageTable& table, usize length)
        : m_table {move(table)}
        , m_origin {&origin}
    {
        this->resize(length);
    }

    template <class Type>
    PagedArray<Type>::PagedArray(PageAlloc& origin, void* memory, usize length)
        : m_table {}
        , m_origin {&origin}
    {
        usize page = origin.page();

        create(this->m_table,
            memory,
            length,
            page);
    }

    template <class Type>
    PagedArray<Type>::~PagedArray()
    {
        this->resize(0l);
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
            Part page = this->m_origin->reserve();

            // clang-format off
            // printf("[%2lu. \x1b[32m%p\x1b[0m -> %lu]\n",
            //     ++n, this, page.length());
            // clang-format on

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
