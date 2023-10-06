#include <smal/Memory/PagedArray.hpp>

namespace smal
{
    template <class Type>
    PagedArray<Type>::PagedArray(PageAlloc& origin, long length)
        : m_table {}
        , m_origin {&origin}
    {
        Page page = origin.reserve();

        Common::create(this->m_table,
            page.memory(),
            page.length(),
            page.length());

        if ( length != 0 )
            this->resize(length);
    }

    template <class Type>
    PagedArray<Type>::PagedArray(PageAlloc& origin, PageTable& table, long length)
        : m_table {Common::move(table)}
        , m_origin {&origin}
    {
        if ( length != 0 )
            this->resize(length);
    }

    template <class Type>
    PagedArray<Type>::PagedArray(PageAlloc& origin, void* memory, long length)
        : m_table {}
        , m_origin {&origin}
    {
        long page = origin.page();

        Common::create(this->m_table,
            memory,
            length,
            page);
    }

    template <class Type>
    PagedArray<Type>::~PagedArray()
    { }

    template <class Type>
    long
    PagedArray<Type>::length() const
    {
        long page = this->m_table.page();
        long size = this->m_table.size();

        // Length in values.
        return Math::floor(page, SIZE) * size;
    }

    template <class Type>
    bool
    PagedArray<Type>::resize(long length)
    {
        long page = this->m_table.page();
        long size = this->m_table.size();

        // Length in pages.
        length = Math::ceil(length, Math::floor(page, SIZE));

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
        Page page;

        for ( long i = start; i < start + pages; i++ ) {
            page = this->m_origin->reserve();

            if ( this->m_table.insert(page, i) == false ) {
                this->m_origin->reclaim(page);

                return false;
            }
        }

        return true;
    }

    template <class Type>
    bool
    PagedArray<Type>::detach(long pages)
    {
        long start = this->m_table.size();
        Page page;

        for ( long i = start - 1; i >= start - pages; i-- ) {
            Common::create(page,
                this->m_origin,
                this->m_table.remove(i),
                this->m_table.page());

            if ( this->m_origin->reclaim(page) == false )
                return false;
        }

        return true;
    }

    template <class Type>
    Type&
    PagedArray<Type>::operator[](long index)
    {
        char* addr = this->m_table
                         .search(index, SIZE);

        return *(Type*) addr;
    }

    template <class Type>
    const Type&
    PagedArray<Type>::operator[](long index) const
    {
        char* addr = this->m_table
                         .search(index, SIZE);

        return *(Type*) addr;
    }
} // namespace smal
