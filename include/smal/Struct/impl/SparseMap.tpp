#include <smal/Struct/SparseMap.hpp>

namespace smal
{
    template <class Type, template <class> class Array>
    SparseMap<Type, Array>::SparseMap()
        : m_table {}
        , m_dense {}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    SparseMap<Type, Array>::SparseMap(const PagedArray<long>& table, const PagedArray<long>& dense, const Array<Type>& array)
        : m_table {Common::move(table)}
        , m_dense {Common::move(dense)}
        , m_array {Common::move(array)}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    long
    SparseMap<Type, Array>::length() const
    {
        return this->m_array.length();
    }

    template <class Type, template <class> class Array>
    long
    SparseMap<Type, Array>::size() const
    {
        return this->m_size;
    }

    template <class Type, template <class> class Array>
    bool
    SparseMap<Type, Array>::isFull() const
    {
        return this->m_size == this->m_array.length();
    }

    template <class Type, template <class> class Array>
    bool
    SparseMap<Type, Array>::isEmpty() const
    {
        return this->m_size == 0;
    }

    template <class Type, template <class> class Array>
    bool
    SparseMap<Type, Array>::insert(long key, const Type& item)
    {
        long idx = this->m_size;

        if ( this->isFull() ) return false;

        if ( this->contains(key) == false ) {
            this->m_size += 1;

            this->m_table[key] = idx;
            this->m_dense[idx] = key;

            Common::create(this->m_array[idx], item);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseMap<Type, Array>::insert(long key, Type&& item)
    {
        long idx = this->m_size;

        if ( this->isFull() ) return false;

        if ( this->contains(key) == false ) {
            this->m_size += 1;

            this->m_table[key] = idx;
            this->m_dense[idx] = key;

            Common::create(this->m_array[idx], Common::move(item));

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseMap<Type, Array>::remove(long key)
    {
        long idx = 0, lst = 0;

        if ( this->isEmpty() == true ) return false;

        if ( this->contains(key) == true ) {
            idx = this->m_table[key];
            lst = this->m_dense[this->m_size];

            this->m_size -= 1;

            this->m_dense[lst] = idx;
            this->m_table[idx] = lst;
            this->m_array[idx] = this->m_array[lst];

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseMap<Type, Array>::contains(long key) const
    {
        long idx = this->m_table[key];

        if ( idx < this->m_size ) {
            if ( this->m_dense[idx] == key )
                return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseMap<Type, Array>::resize(long len1, long len2)
    {
        this->m_table.resize(len1);
        this->m_dense.resize(len2);

        return this->m_array.resize(len2);
    }

    template <class Type, template <class> class Array>
    long
    SparseMap<Type, Array>::keyOf(long index) const
    {
        return this->m_dense[index];
    }

    template <class Type, template <class> class Array>
    long
    SparseMap<Type, Array>::indexOf(long key) const
    {
        return this->m_table[key];
    }

    template <class Type, template <class> class Array>
    Type&
    SparseMap<Type, Array>::access(long index)
    {
        if ( index < 0 )
            index = this->m_size + index;

        return this->m_array[index];
    }

    template <class Type, template <class> class Array>
    const Type&
    SparseMap<Type, Array>::access(long index) const
    {
        if ( index < 0 )
            index = this->m_size + index;

        return this->m_array[index];
    }

    template <class Type, template <class> class Array>
    Type&
    SparseMap<Type, Array>::operator[](long index)
    {
        return this->m_array[index];
    }

    template <class Type, template <class> class Array>
    const Type&
    SparseMap<Type, Array>::operator[](long index) const
    {
        return this->m_array[index];
    }
} // namespace smal
