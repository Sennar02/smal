#include <smal/Struct/SparseTable.hpp>

namespace smal
{
    using namespace Common;

    template <class Type, template <class> class Array>
    SparseTable<Type, Array>::SparseTable()
        : m_sparse {}
        , m_packed {}
        , m_array {}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    SparseTable<Type, Array>::SparseTable(
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
    SparseTable<Type, Array>::length() const
    {
        return this->m_packed.length();
    }

    template <class Type, template <class> class Array>
    long
    SparseTable<Type, Array>::size() const
    {
        return this->m_size;
    }

    template <class Type, template <class> class Array>
    bool
    SparseTable<Type, Array>::isFull() const
    {
        return this->m_size == this->m_packed.length();
    }

    template <class Type, template <class> class Array>
    bool
    SparseTable<Type, Array>::isEmpty() const
    {
        return this->m_size == 0;
    }

    template <class Type, template <class> class Array>
    PagedArray<long>&
    SparseTable<Type, Array>::sparse()
    {
        return this->m_sparse;
    }

    template <class Type, template <class> class Array>
    const PagedArray<long>&
    SparseTable<Type, Array>::sparse() const
    {
        return this->m_sparse;
    }

    template <class Type, template <class> class Array>
    Array<long>&
    SparseTable<Type, Array>::packed()
    {
        return this->m_packed;
    }

    template <class Type, template <class> class Array>
    const Array<long>&
    SparseTable<Type, Array>::packed() const
    {
        return this->m_packed;
    }

    template <class Type, template <class> class Array>
    Array<Type>&
    SparseTable<Type, Array>::values()
    {
        return this->m_values;
    }

    template <class Type, template <class> class Array>
    const Array<Type>&
    SparseTable<Type, Array>::values() const
    {
        return this->m_values;
    }

    template <class Type, template <class> class Array>
    bool
    SparseTable<Type, Array>::insert(const long& key, const Type& value)
    {
        long idx = this->m_size;

        if ( this->isFull() == false ) {
            if ( this->contains(key) == false ) {
                this->m_size += 1;

                this->m_sparse[key] = idx;
                this->m_packed[idx] = key;

                create(this->m_array[idx], value);

                return true;
            }
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseTable<Type, Array>::insert(const long& key, Type&& value)
    {
        long idx = this->m_size;

        if ( this->isFull() == false ) {
            if ( this->contains(key) == false ) {
                this->m_size += 1;

                this->m_sparse[key] = idx;
                this->m_packed[idx] = key;

                create(this->m_array[idx], move(value));

                return true;
            }
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseTable<Type, Array>::remove(const long& key)
    {
        long idx = 0, last = 0;

        if ( this->isEmpty() == true ) return false;

        if ( this->contains(key) == true ) {
            idx  = this->m_sparse[key];
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
    SparseTable<Type, Array>::contains(const long& key) const
    {
        long idx = this->m_sparse[key];

        if ( idx < this->m_size ) {
            if ( this->m_packed[idx] == key )
                return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseTable<Type, Array>::resize(long sparse, long packed)
    {
        return this->m_sparse.resize(sparse) &&
               this->m_packed.resize(packed) &&
               this->m_array.resize(packed);
    }

    template <class Type, template <class> class Array>
    Type&
    SparseTable<Type, Array>::operator[](const long& index)
    {
        if ( index < 0 )
            return this->m_array[this->m_size + index];

        return this->m_array[index];
    }

    template <class Type, template <class> class Array>
    const Type&
    SparseTable<Type, Array>::operator[](const long& index) const
    {
        if ( index < 0 )
            return this->m_array[this->m_size + index];

        return this->m_array[index];
    }
} // namespace smal
