#include <smal/Struct/Data/SparseMap.hpp>

namespace ma
{
    template <class Type, template <class> class Array>
    SparseMap<Type, Array>::SparseMap()
        : m_sparse {}
        , m_packed {}
        , m_array {}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    SparseMap<Type, Array>::SparseMap(BaseOrigin* origin, usize length)
        : m_sparse {origin, length}
        , m_packed {origin, length}
        , m_array {origin, length}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    SparseMap<Type, Array>::SparseMap(const Array<Type>& values)
        : m_sparse {}
        , m_packed {}
        , m_array {move(values)}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    usize
    SparseMap<Type, Array>::capacity() const
    {
        return this->m_array.length();
    }

    template <class Type, template <class> class Array>
    usize
    SparseMap<Type, Array>::count() const
    {
        return this->m_size;
    }

    template <class Type, template <class> class Array>
    bool
    SparseMap<Type, Array>::is_empty() const
    {
        return this->m_size == 0;
    }

    template <class Type, template <class> class Array>
    bool
    SparseMap<Type, Array>::is_full() const
    {
        return this->m_size == this->m_array.length();
    }

    template <class Type, template <class> class Array>
    template <class Func>
    bool
    SparseMap<Type, Array>::contains(usize key, Func comp) const
    {
        usize index = 0;

        if ( key >= this->m_sparse.length() )
            return false;

        index = this->m_sparse[key];

        if ( index < this->m_size ) {
            if ( comp(this->m_packed[index], key) )
                return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseMap<Type, Array>::contains(usize key) const
    {
        return this->contains(key, [](auto& a, auto& b) {
            return a == b;
        });
    }

    template <class Type, template <class> class Array>
    template <class Func>
    isize
    SparseMap<Type, Array>::indexOf(usize key, Func comp) const
    {
        usize index = 0;

        if ( key >= this->m_sparse.length() )
            return -1;

        index = this->m_sparse[key];

        if ( index < this->m_size )
            return index;

        return -1;
    }

    template <class Type, template <class> class Array>
    isize
    SparseMap<Type, Array>::indexOf(usize key) const
    {
        return this->indexOf(key, [](auto& a, auto& b) {
            return a == b;
        });
    }

    template <class Type, template <class> class Array>
    template <class Func>
    isize
    SparseMap<Type, Array>::keyOf(usize index, Func comp) const
    {
        usize key = 0;

        if ( index >= this->m_size )
            return -1;

        key = this->m_packed[index];

        if ( key < this->m_sparse.length() )
            return key;

        return -1;
    }

    template <class Type, template <class> class Array>
    isize
    SparseMap<Type, Array>::keyOf(usize index) const
    {
        return this->keyOf(index, [](auto& a, auto& b) {
            return a == b;
        });
    }

    template <class Type, template <class> class Array>
    template <class Func>
    void
    SparseMap<Type, Array>::forEach(Func oper) const
    {
        for ( usize i = 0; i < this->m_size; i++ )
            oper(this->m_array[i], i, this->keyOf(i));
    }

    template <class Type, template <class> class Array>
    SparseMap<Type, Array>
    SparseMap<Type, Array>::clone(BaseOrigin* origin) const
    {
        SparseMap<Type, Array> other = {origin, this->m_size};

        for ( usize i = 0; i < this->m_size; i++ )
            other.insert(this->keyOf(i), this->m_array[i]);

        return other;
    }

    template <class Type, template <class> class Array>
    bool
    SparseMap<Type, Array>::insert(usize key, const Type& value)
    {
        usize idx = this->m_size;

        if ( this->contains(key) == true )
            return false;

        if ( this->growTo(key) == true ) {
            if ( this->is_full() == false ) {
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
    SparseMap<Type, Array>::insert(usize key, Type&& value)
    {
        usize idx = this->m_size;

        if ( this->contains(key) == true )
            return false;

        if ( this->growTo(key) == true ) {
            if ( this->is_full() == false ) {
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
    SparseMap<Type, Array>::remove(usize key)
    {
        usize pos = this->m_size - 1;
        usize idx = 0;
        usize tmp = 0;

        if ( this->contains(key) == true ) {
            this->m_size -= 1;

            idx = this->m_sparse[key];
            tmp = this->m_packed[pos];

            this->m_sparse[tmp] = idx;
            this->m_packed[idx] = tmp;

            swap(this->m_array[idx],
                this->m_array[pos]);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    SparseMap<Type, Array>::resize(usize sparse, usize packed)
    {
        bool oper = true;

        oper &= this->m_sparse.resize(sparse);
        oper &= this->m_packed.resize(packed);
        oper &= this->m_array.resize(packed);

        return oper;
    }

    template <class Type, template <class> class Array>
    template <class Algo, class Comp>
    void
    SparseMap<Type, Array>::sort(Comp comp)
    {
        usize curr = 0;
        usize next = 0;

        Algo::sort(this->m_packed, this->m_size, comp);

        for ( usize i = 0; i < this->m_size; i++ ) {
            curr = i;
            next = this->m_sparse[this->m_packed[curr]];

            while ( curr != next ) {
                auto i = this->m_packed[curr];
                auto j = this->m_packed[next];

                swap(this->m_array[this->m_sparse[i]],
                    this->m_array[this->m_sparse[j]]);

                this->m_sparse[i] = curr;

                curr = next;
                next = this->m_sparse[j];
            }
        }
    }

    template <class Type, template <class> class Array>
    PagedArray<usize>&
    SparseMap<Type, Array>::sparse()
    {
        return this->m_sparse;
    }

    template <class Type, template <class> class Array>
    const PagedArray<usize>&
    SparseMap<Type, Array>::sparse() const
    {
        return this->m_sparse;
    }

    template <class Type, template <class> class Array>
    PagedArray<usize>&
    SparseMap<Type, Array>::packed()
    {
        return this->m_packed;
    }

    template <class Type, template <class> class Array>
    const PagedArray<usize>&
    SparseMap<Type, Array>::packed() const
    {
        return this->m_packed;
    }

    template <class Type, template <class> class Array>
    Array<Type>&
    SparseMap<Type, Array>::values()
    {
        return this->m_array;
    }

    template <class Type, template <class> class Array>
    const Array<Type>&
    SparseMap<Type, Array>::values() const
    {
        return this->m_array;
    }

    template <class Type, template <class> class Array>
    Type&
    SparseMap<Type, Array>::find(usize index)
    {
        return this->m_array[index];
    }

    template <class Type, template <class> class Array>
    const Type&
    SparseMap<Type, Array>::find(usize index) const
    {
        return this->m_array[index];
    }

    template <class Type, template <class> class Array>
    Type&
    SparseMap<Type, Array>::operator[](usize index)
    {
        return this->find(index);
    }

    template <class Type, template <class> class Array>
    const Type&
    SparseMap<Type, Array>::operator[](usize index) const
    {
        return this->find(index);
    }

    template <class Type, template <class> class Array>
    bool
    SparseMap<Type, Array>::growTo(usize key)
    {
        usize idx = this->m_size;
        usize len = 0;

        if ( idx == this->m_array.length() )
            if ( this->m_array.resize(idx * 1.5f + 16) == false )
                return false;

        while ( this->m_sparse.length() <= key ) {
            len = this->m_sparse.length() * 1.5f + 16;

            if ( this->m_sparse.resize(len) == false )
                return false;
        }

        if ( idx == this->m_packed.length() )
            if ( this->m_packed.resize(idx * 1.5f + 16) == false )
                return false;

        return true;
    }
} // namespace ma
