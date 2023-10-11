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

        if ( this->contains(key) == true ) return false;

        if ( this->isFull() == true )
            this->resize(1.0f, 1.5f);

        if ( this->isFull() == false ) {
            if ( this->m_sparse.length() <= key )
                this->resize(Math::max(1l, key), -1);

            this->m_size += 1;

            this->m_sparse[key] = idx;
            this->m_packed[idx] = key;

            create(this->m_array[idx], value);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseTable<Type, Array>::insert(const long& key, Type&& value)
    {
        long idx = this->m_size;

        if ( this->contains(key) == true ) return false;

        if ( this->isFull() == true )
            this->resize(1.0f, 1.5f);

        if ( this->isFull() == false ) {
            if ( this->m_sparse.length() <= key )
                this->resize(Math::max(1l, key), -1);

            this->m_size += 1;

            this->m_sparse[key] = idx;
            this->m_packed[idx] = key;

            create(this->m_array[idx], move(value));

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseTable<Type, Array>::remove(const long& key)
    {
        long idx = 0, last = 0;

        if ( this->contains(key) == true ) {
            this->m_size -= 1;

            idx  = this->m_sparse[key];
            last = this->m_packed[this->m_size];

            this->m_packed[last] = idx;
            this->m_sparse[idx]  = last;

            swap(this->m_array[idx], this->m_array[last]);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseTable<Type, Array>::contains(const long& key) const
    {
        long idx = this->m_size;

        if ( this->m_sparse.length() <= key )
            return false;

        idx = this->m_sparse[key];

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
        bool oper = true;

        if ( sparse != -1 )
            oper &= this->m_sparse.resize(sparse);

        if ( packed != -1 ) {
            oper &= this->m_packed.resize(packed);
            oper &= this->m_array.resize(packed);
        }

        return oper;
    }

    template <class Type, template <class> class Array>
    bool
    SparseTable<Type, Array>::resize(float sparse, float packed)
    {
        long length1 = Math::max(16l, this->m_sparse.length());
        long length2 = Math::max(16l, this->m_packed.length());

        return this->resize(
            (long) sparse * length1,
            (long) packed * length2);
    }

    template <class Type, template <class> class Array>
    Type&
    SparseTable<Type, Array>::valueOf(const long& key)
    {
        return this->m_array[this->m_sparse[key]];
    }

    template <class Type, template <class> class Array>
    const Type&
    SparseTable<Type, Array>::valueOf(const long& key) const
    {
        return this->m_array[this->m_sparse[key]];
    }

    template <class Type, template <class> class Array>
    Type&
    SparseTable<Type, Array>::operator[](const long& index)
    {
        return this->m_array[index];
    }

    template <class Type, template <class> class Array>
    const Type&
    SparseTable<Type, Array>::operator[](const long& index) const
    {
        return this->m_array[index];
    }
} // namespace smal
