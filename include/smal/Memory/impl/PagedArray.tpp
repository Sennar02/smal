#include <smal/Memory/PagedArray.hpp>

namespace smal
{
    template <class Type>
    PagedArray<Type>::PagedArray()
        : m_table {}
        , m_origin {0}
    { }

    template <class Type>
    PagedArray<Type>::PagedArray(PageAlloc& origin, long length)
        : m_table {}
        , m_origin {&origin}
    {
        Part page = origin.reserve();

        this->m_table = create(this->m_table,
            page.memory(),
            page.length(),
            page.length());

        this->resize(length);
    }

    template <class Type>
    PagedArray<Type>::PagedArray(PageAlloc& origin, PageTable& table, long length)
        : m_table {move(table)}
        , m_origin {&origin}
    {
        this->resize(length);
    }

    template <class Type>
    PagedArray<Type>::PagedArray(PageAlloc& origin, void* memory, long length)
        : m_table {}
        , m_origin {&origin}
    {
        long page = origin.page();

        this->m_table = create(this->m_table,
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
    long
    PagedArray<Type>::length() const
    {
        long page = this->m_table.page();
        long size = this->m_table.size();
        long fact = Math::floor(page, SIZE); // items per page.

        return fact * size;
    }

    template <class Type>
    bool
    PagedArray<Type>::resize(long length)
    {
        long page = this->m_table.page();
        long size = this->m_table.size();
        long fact = Math::floor(page, SIZE); // items per page.

        length = Math::ceil(length, fact);

        if ( length > size )
            return this->attach(length - size);
        else
            return this->detach(size - length);
    }

    template <class Type>
    bool
    PagedArray<Type>::attach(long pages)
    {
        long start = this->m_table.size();

        for ( long i = start; i < start + pages; i++ ) {
            Part page = this->m_origin->reserve();

            if ( this->m_table.insert(page, i) )
                continue;

            this->m_origin->reclaim(page);

            return false;
        }

        return true;
    }

    template <class Type>
    bool
    PagedArray<Type>::detach(long pages)
    {
        long start = this->m_table.size();

        for ( long i = start - 1; i >= start - pages; i-- ) {
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
    PagedArray<Type>::operator[](long index)
    {
        auto item =
            this->m_table.lookup(index, SIZE);

        return *(Type*) item;
    }

    template <class Type>
    const Type&
    PagedArray<Type>::operator[](long index) const
    {
        auto item =
            this->m_table.lookup(index, SIZE);

        return *(const Type*) item;
    }
} // namespace smal
