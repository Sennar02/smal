#include <smal/Struct/ArrayList.hpp>

namespace smal
{
    template <class Type, template <class> class Array>
    ArrayList<Type, Array>::ArrayList()
        : m_array {}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    ArrayList<Type, Array>::ArrayList(BaseOrigin* origin, usize length)
        : m_array {(PoolOrigin*) origin, length}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    ArrayList<Type, Array>::ArrayList(const Array<Type>& values)
        : m_array {move(values)}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    usize
    ArrayList<Type, Array>::capacity() const
    {
        return this->m_array.length();
    }

    template <class Type, template <class> class Array>
    usize
    ArrayList<Type, Array>::size() const
    {
        return this->m_size;
    }

    template <class Type, template <class> class Array>
    bool
    ArrayList<Type, Array>::isEmpty() const
    {
        return this->m_size == 0;
    }

    template <class Type, template <class> class Array>
    bool
    ArrayList<Type, Array>::isFull() const
    {
        return this->m_size == this->m_array.length();
    }

    template <class Type, template <class> class Array>
    template <class Cmpr>
    bool
    ArrayList<Type, Array>::contains(const Type& value, Cmpr func) const
    {
        for ( usize i = 0; i < this->m_size; i++ ) {
            if ( func(this->m_array[i], value) == true )
                return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    ArrayList<Type, Array>::insert(const Type& value, usize index)
    {
        auto& self = *this;

        if ( this->isFull() == true )
            this->resize(this->m_size * 1.5f + 16);

        if ( this->isFull() == false ) {
            index = Math::min(this->m_size, index);

            for ( usize i = this->m_size; i > index; i-- )
                self[i] = move(self[i - 1]);

            this->m_size += 1;
            create(self[index], value);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    ArrayList<Type, Array>::insert(Type&& value, usize index)
    {
        auto& self = *this;

        if ( this->isFull() == true )
            this->resize(this->m_size * 1.5f + 16);

        if ( this->isFull() == false ) {
            index = Math::min(this->m_size, index);

            for ( usize i = this->m_size; i > index; i-- )
                self[i] = move(self[i - 1]);

            this->m_size += 1;
            create(self[index], move(value));

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    ArrayList<Type, Array>::remove(usize index)
    {
        auto& self = *this;

        if ( this->isEmpty() == false ) {
            index = Math::min(this->m_size, index);
            this->m_size -= 1;

            for ( usize i = index; i < this->m_size; i++ )
                self[i] = move(self[i + 1]);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    ArrayList<Type, Array>::resize(usize length)
    {
        return this->m_array.resize(length);
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
        if ( index < 0 )
            index = this->m_size + index;

        return this->m_array[index];
    }

    template <class Type, template <class> class Array>
    const Type&
    ArrayList<Type, Array>::find(isize index) const
    {
        if ( index < 0 )
            index = this->m_size + index;

        return this->m_array[index];
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
} // namespace smal
