#include <smal/Struct/Vector.hpp>

namespace smal
{
    template <class Type>
    Vector<Type>::Vector(PageAlloc& origin, PageTable& ptable)
        : m_origin {&origin}
        , m_ptable {&ptable}
        , m_size {0}
    { }

    template <class Type>
    Vector<Type>::~Vector()
    { }

    template <class Type>
    long
    Vector<Type>::length() const
    {
        long page = this->m_ptable->page();
        long size = this->m_ptable->size();

        return Math::floor(page, TYPE_SIZE) * size;
    }

    template <class Type>
    long
    Vector<Type>::size() const
    {
        return this->m_size;
    }

    template <class Type>
    bool
    Vector<Type>::isFull() const
    {
        return this->m_size == this->length();
    }

    template <class Type>
    bool
    Vector<Type>::isEmpty() const
    {
        return this->m_size == 0;
    }

    template <class Type>
    bool
    Vector<Type>::resize(long length)
    {
        long page = this->m_ptable->page();
        long size = this->m_ptable->size();

        long pages = Math::ceil(length * TYPE_SIZE, page);

        if ( pages > size )
            return this->expand(pages - size);

        return this->shrink(size - pages);
    }

    template <class Type>
    bool
    Vector<Type>::insert(const Type& item, long index)
    {
        auto& self = *this;

        if ( index == -1 ) index = this->m_size;

        if ( this->isFull() == false ) {
            index = Math::min(index, this->m_size);

            for ( long i = this->m_size; i > index; i-- )
                self[i] = Common::move(self[i - 1]);

            this->m_size += 1;

            Common::create(self[index], item);

            return true;
        }

        return false;
    }

    template <class Type>
    bool
    Vector<Type>::insert(Type&& item, long index)
    {
        auto& self = *this;

        if ( index == -1 ) index = this->m_size;

        if ( this->isFull() == false ) {
            index = Math::min(index, this->m_size);

            for ( long i = this->m_size; i > index; i-- )
                self[i] = Common::move(self[i - 1]);

            Common::create(self[index], Common::move(item));

            this->m_size += 1;
            return true;
        }

        return false;
    }

    template <class Type>
    bool
    Vector<Type>::remove(long index)
    {
        auto& self = *this;

        if ( index == -1 ) index = this->m_size - 1;

        if ( this->isEmpty() == false ) {
            index = Math::min(index, this->m_size - 1);

            for ( long i = index; i < this->m_size - 1; i++ )
                self[i] = Common::move(self[i + 1]);

            this->m_size -= 1;
            return true;
        }

        return false;
    }

    template <class Type>
    Type&
    Vector<Type>::operator[](long index)
    {
        char* addr = this->m_ptable->lookup(
            index, TYPE_SIZE);

        return *(Type*) addr;
    }

    template <class Type>
    const Type&
    Vector<Type>::operator[](long index) const
    {
        char* addr = this->m_ptable->lookup(
            index, TYPE_SIZE);

        return *(Type*) addr;
    }

    template <class Type>
    bool
    Vector<Type>::expand(long pages)
    {
        long start = this->m_ptable->size();

        for ( long i = start; i < start + pages; i++ ) {
            Page page = this->m_origin->reserve();
            bool oper = this->m_ptable->insert(page, i);

            if ( oper == false ) {
                this->m_origin->reclaim(page);

                return false;
            }
        }

        return true;
    }

    template <class Type>
    bool
    Vector<Type>::shrink(long pages)
    {
        long start = this->m_ptable->size();

        for ( long i = start - 1; i >= start - pages; i-- ) {
            Page page = this->m_ptable->remove(i);

            bool oper = this->m_origin->reclaim({
                this->m_origin,
                page.memory(),
                page.length(),
            });

            if ( oper == false )
                return false;
        }

        return true;
    }
} // namespace smal
