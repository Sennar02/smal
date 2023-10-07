#include <smal/Struct/SparseSet.hpp>

namespace smal
{
    using namespace Common;

    template <class Type, template <class> class Array>
    SparseSet<Type, Array>::SparseSet()
        : m_sparse {}
        , m_packed {}
        , m_array {}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    SparseSet<Type, Array>::SparseSet(
        const PagedArray<long>& sparse,
        const Array<long>&      packed,
        const Array<Type>&      array)
        : m_sparse {move(sparse)}
        , m_packed {move(packed)}
        , m_array {move(array)}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    long
    SparseSet<Type, Array>::length() const
    {
        return this->m_packed.length();
    }

    template <class Type, template <class> class Array>
    long
    SparseSet<Type, Array>::size() const
    {
        return this->m_size;
    }

    template <class Type, template <class> class Array>
    bool
    SparseSet<Type, Array>::isFull() const
    {
        return this->m_size == this->m_packed.length();
    }

    template <class Type, template <class> class Array>
    bool
    SparseSet<Type, Array>::isEmpty() const
    {
        return this->m_size == 0;
    }

    template <class Type, template <class> class Array>
    PagedArray<long>&
    SparseSet<Type, Array>::sparse()
    {
        return this->m_sparse;
    }

    template <class Type, template <class> class Array>
    const PagedArray<long>&
    SparseSet<Type, Array>::sparse() const
    {
        return this->m_sparse;
    }

    template <class Type, template <class> class Array>
    Array<long>&
    SparseSet<Type, Array>::packed()
    {
        return this->m_packed;
    }

    template <class Type, template <class> class Array>
    const Array<long>&
    SparseSet<Type, Array>::packed() const
    {
        return this->m_packed;
    }

    template <class Type, template <class> class Array>
    Array<Type>&
    SparseSet<Type, Array>::values()
    {
        return this->m_values;
    }

    template <class Type, template <class> class Array>
    const Array<Type>&
    SparseSet<Type, Array>::values() const
    {
        return this->m_values;
    }

    template <class Type, template <class> class Array>
    bool
    SparseSet<Type, Array>::insert(long item, const Type& value)
    {
        long idx = this->m_size;

        if ( this->isFull() == false ) {
            if ( this->contains(item) == false ) {
                this->m_size += 1;

                this->m_sparse[item] = idx;
                this->m_packed[idx]  = item;

                create(this->m_array[idx], value);

                return true;
            }
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseSet<Type, Array>::insert(long item, Type&& value)
    {
        long idx = this->m_size;

        if ( this->isFull() == false ) {
            if ( this->contains(item) == false ) {
                this->m_size += 1;

                this->m_sparse[item] = idx;
                this->m_packed[idx]  = item;

                create(this->m_array[idx], move(value));

                return true;
            }
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseSet<Type, Array>::remove(long item)
    {
        long idx = 0, last = 0;

        if ( this->isEmpty() == true ) return false;

        if ( this->contains(item) == true ) {
            idx  = this->m_sparse[item];
            last = this->m_packed[this->m_size];

            this->m_size -= 1;

            this->m_packed[last] = idx;
            this->m_sparse[idx]  = last;

            swap(this->m_array[idx],
                this->m_array[last]);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseSet<Type, Array>::contains(long item) const
    {
        long idx = this->m_sparse[item];

        if ( idx < this->m_size ) {
            if ( this->m_packed[idx] == item )
                return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseSet<Type, Array>::resize(long sparse, long packed)
    {
        return this->m_sparse.resize(sparse) &&
               this->m_packed.resize(packed) &&
               this->m_array.resize(packed);
    }

    template <class Type, template <class> class Array>
    Type&
    SparseSet<Type, Array>::operator[](long index)
    {
        if ( index < 0 )
            index = this->m_size + index;

        return this->m_array[index];
    }

    template <class Type, template <class> class Array>
    const Type&
    SparseSet<Type, Array>::operator[](long index) const
    {
        if ( index < 0 )
            index = this->m_size + index;

        return this->m_array[index];
    }
} // namespace smal
