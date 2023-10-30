#include <smal/Struct/Data/ArrayList.hpp>

namespace ma
{
    template <class Type, template <class> class Array>
    ArrayList<Type, Array>::ArrayList()
        : m_array {}
        , m_count {0}
    { }

    template <class Type, template <class> class Array>
    ArrayList<Type, Array>::ArrayList(BaseOrigin* origin, usize size)
        : m_array {origin, size}
        , m_count {0}
    { }

    template <class Type, template <class> class Array>
    ArrayList<Type, Array>::ArrayList(const Array<Type>& values)
        : m_array {move(values)}
        , m_count {0}
    { }

    template <class Type, template <class> class Array>
    usize
    ArrayList<Type, Array>::size() const
    {
        return this->m_array.size();
    }

    template <class Type, template <class> class Array>
    usize
    ArrayList<Type, Array>::count() const
    {
        return this->m_count;
    }

    template <class Type, template <class> class Array>
    bool
    ArrayList<Type, Array>::is_empty() const
    {
        return this->m_count == 0;
    }

    template <class Type, template <class> class Array>
    bool
    ArrayList<Type, Array>::is_full() const
    {
        return this->m_count == this->m_array.size();
    }

    template <class Type, template <class> class Array>
    template <class Func>
    bool
    ArrayList<Type, Array>::contains(const Type& value, Func comp) const
    {
        for ( usize i = 0; i < this->m_count; i++ ) {
            if ( comp(this->m_array[i], value) == true )
                return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    ArrayList<Type, Array>::contains(const Type& value) const
    {
        return this->contains(value, [](auto& a, auto& b) {
            return a == b;
        });
    }

    template <class Type, template <class> class Array>
    template <class Func>
    isize
    ArrayList<Type, Array>::index_of(const Type& value, Func comp) const
    {
        for ( usize i = 0; i < this->m_count; i++ ) {
            if ( comp(this->m_array[i], value) == true )
                return i;
        }

        return -1;
    }

    template <class Type, template <class> class Array>
    isize
    ArrayList<Type, Array>::index_of(const Type& value) const
    {
        return this->index_of(value, [](auto& a, auto& b) {
            return a == b;
        });
    }

    template <class Type, template <class> class Array>
    template <class Func>
    void
    ArrayList<Type, Array>::for_each(Func oper) const
    {
        for ( usize i = 0; i < this->m_count; i++ )
            oper(this->m_array[i], i);
    }

    template <class Type, template <class> class Array>
    ArrayList<Type, Array>
    ArrayList<Type, Array>::clone(BaseOrigin* origin) const
    {
        ArrayList<Type, Array> other = {origin, this->m_count};

        for ( usize i = 0; i < this->m_count; i++ )
            other.insert(this->m_array[i]);

        return other;
    }

    template <class Type, template <class> class Array>
    bool
    ArrayList<Type, Array>::insert(const Type& value, isize index)
    {
        usize place = 0;

        if ( this->is_full() == true )
            this->resize(this->m_count * 1.5f + 16);

        if ( this->is_full() == false ) {
            place = this->limit(index, this->m_count + 1);

            this->m_count += 1;

            for ( usize i = this->m_count - 1; i > place; i-- )
                this->m_array[i] = move(this->m_array[i - 1]);

            create(this->m_array[place], value);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    ArrayList<Type, Array>::insert(Type&& value, isize index)
    {
        usize place = 0;

        if ( this->is_full() == true )
            this->resize(this->m_count * 1.5f + 16);

        if ( this->is_full() == false ) {
            place = this->limit(index, this->m_count + 1);

            this->m_count += 1;

            for ( usize i = this->m_count - 1; i > place; i-- )
                this->m_array[i] = move(this->m_array[i - 1]);

            create(this->m_array[place], move(value));

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    ArrayList<Type, Array>::remove(isize index)
    {
        usize place = 0;

        if ( this->is_empty() == false ) {
            place = this->limit(index, this->m_count);

            this->m_count -= 1;

            for ( usize i = place; i < this->m_count; i++ )
                this->m_array[i] = move(this->m_array[i + 1]);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    ArrayList<Type, Array>::resize(usize size)
    {
        return this->m_array.resize(size);
    }

    template <class Type, template <class> class Array>
    template <class Algo, class Comp>
    void
    ArrayList<Type, Array>::sort(Comp comp)
    {
        Algo::sort(this->m_array, this->m_count, comp);
    }

    template <class Type, template <class> class Array>
    Array<Type>&
    ArrayList<Type, Array>::values()
    {
        return this->m_array;
    }

    template <class Type, template <class> class Array>
    const Array<Type>&
    ArrayList<Type, Array>::values() const
    {
        return this->m_array;
    }

    template <class Type, template <class> class Array>
    Type&
    ArrayList<Type, Array>::find(isize index)
    {
        return this->m_array[this->limit(index, this->m_count)];
    }

    template <class Type, template <class> class Array>
    const Type&
    ArrayList<Type, Array>::find(isize index) const
    {
        return this->m_array[this->limit(index, this->m_count)];
    }

    template <class Type, template <class> class Array>
    Type&
    ArrayList<Type, Array>::operator[](isize index)
    {
        return this->find(index);
    }

    template <class Type, template <class> class Array>
    const Type&
    ArrayList<Type, Array>::operator[](isize index) const
    {
        return this->find(index);
    }

    template <class Type, template <class> class Array>
    usize
    ArrayList<Type, Array>::limit(isize index, usize limit) const
    {
        usize place = 0;

        if ( index < 0 )
            index = limit + index;

        place = Math::max(index, (isize) 0);
        place = Math::min(place, limit);

        return place;
    }
} // namespace ma
