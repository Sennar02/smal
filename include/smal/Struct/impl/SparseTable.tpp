#include <smal/Struct/SparseTable.hpp>

namespace smal
{
    template <class Type, template <class> class Array>
    SparseTable<Type, Array>::SparseTable()
        : m_sparse {}
        , m_packed {}
        , m_array {}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    SparseTable<Type, Array>::SparseTable(PageAlloc& origin, usize length)
        : m_sparse {origin, length}
        , m_packed {origin, length}
        , m_array {origin, length}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    SparseTable<Type, Array>::SparseTable(
        const PagedArray<usize>& sparse,
        const PagedArray<usize>& packed,
        const Array<Type>&       array)
        : m_sparse {move(sparse)}
        , m_packed {move(packed)}
        , m_array {move(array)}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    usize
    SparseTable<Type, Array>::length() const
    {
        usize packed = this->m_array.length();
        usize values = this->m_array.length();

        return Math::min(packed, values);
    }

    template <class Type, template <class> class Array>
    usize
    SparseTable<Type, Array>::size() const
    {
        return this->m_size;
    }

    template <class Type, template <class> class Array>
    bool
    SparseTable<Type, Array>::isFull() const
    {
        return this->m_size == this->length();
    }

    template <class Type, template <class> class Array>
    bool
    SparseTable<Type, Array>::isEmpty() const
    {
        return this->m_size == 0;
    }

    template <class Type, template <class> class Array>
    PagedArray<usize>&
    SparseTable<Type, Array>::sparse()
    {
        return this->m_sparse;
    }

    template <class Type, template <class> class Array>
    const PagedArray<usize>&
    SparseTable<Type, Array>::sparse() const
    {
        return this->m_sparse;
    }

    template <class Type, template <class> class Array>
    PagedArray<usize>&
    SparseTable<Type, Array>::packed()
    {
        return this->m_packed;
    }

    template <class Type, template <class> class Array>
    const PagedArray<usize>&
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
    SparseTable<Type, Array>::insert(const usize& key, const Type& value)
    {
        usize idx = this->m_size;

        if ( this->contains(key) == true )
            return false;

        if ( this->resize(key) == true ) {
            if ( this->isFull() == false ) {
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
    SparseTable<Type, Array>::insert(const usize& key, Type&& value)
    {
        usize idx = this->m_size;

        if ( this->contains(key) == true )
            return false;

        if ( this->resize(key) == true ) {
            if ( this->isFull() == false ) {
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
    SparseTable<Type, Array>::remove(const usize& key)
    {
        usize idx = 0, last = 0;

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
    SparseTable<Type, Array>::contains(const usize& key) const
    {
        usize idx = 0;

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
    SparseTable<Type, Array>::resize(usize sparse, usize packed, usize values)
    {
        bool s = this->m_sparse.resize(sparse);
        bool p = this->m_sparse.resize(sparse);
        bool v = this->m_sparse.resize(sparse);

        return s && p && v;
    }

    template <class Type, template <class> class Array>
    bool
    SparseTable<Type, Array>::resize(const usize& key)
    {
        usize size = 0;

        while ( this->m_sparse.length() <= key ) {
            size = this->m_sparse.length() + 1;

            if ( this->m_sparse.resize(size) == false )
                return false;
        }

        if ( this->m_size == this->m_packed.length() ) {
            if ( this->m_packed.resize(this->m_size * 1.5f + 1) == false )
                return false;
        }

        if ( this->m_size == this->m_array.length() ) {
            if ( this->m_array.resize(this->m_size * 1.5f + 1) == false )
                return false;
        }

        return true;
    }

    template <class Type, template <class> class Array>
    usize
    SparseTable<Type, Array>::indexOf(const usize& key) const
    {
        return key;
    }

    template <class Type, template <class> class Array>
    usize
    SparseTable<Type, Array>::keyOf(const usize& index) const
    {
        return this->m_sparse[index];
    }

    template <class Type, template <class> class Array>
    Type&
    SparseTable<Type, Array>::valueOf(const usize& key)
    {
        return this->m_array[this->m_sparse[key]];
    }

    template <class Type, template <class> class Array>
    const Type&
    SparseTable<Type, Array>::valueOf(const usize& key) const
    {
        return this->m_array[this->m_sparse[key]];
    }

    // template <class Type, template <class> class Array>
    // void
    // SparseTable<Type, Array>::sort(bool (*func)(const usize& value, const usize& other))
    // {
    //     QuickSort::sort(this->m_packed, func, 0, this->m_size);

    //     for ( usize pos = 0; pos < this->m_size; pos++ ) {
    //         usize curr = pos;
    //         usize next = this->m_sparse[this->m_packed[curr]];

    //         while ( curr != next ) {
    //             swap(this->m_array[this->m_sparse[this->m_packed[curr]]],
    //                 this->m_array[this->m_sparse[this->m_packed[next]]]);

    //             this->m_sparse[this->m_packed[curr]] = curr;

    //             curr = next;
    //             next = this->m_sparse[this->m_packed[curr]];
    //         }
    //     }
    // }

    template <class Type, template <class> class Array>
    Type&
    SparseTable<Type, Array>::operator[](const usize& index)
    {
        return this->m_array[index];
    }

    template <class Type, template <class> class Array>
    const Type&
    SparseTable<Type, Array>::operator[](const usize& index) const
    {
        return this->m_array[index];
    }
} // namespace smal
