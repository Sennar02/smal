#include <smal/Struct/Vector.hpp>

namespace smal
{
    template <class Type, template <class> class Array>
    Vector<Type, Array>::Vector()
        : m_array {}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    Vector<Type, Array>::Vector(const Array<Type>& array)
        : m_array {move(array)}
        , m_size {0}
    { }

    template <class Type, template <class> class Array>
    Vector<Type, Array>::~Vector()
    { }

    template <class Type, template <class> class Array>
    usize
    Vector<Type, Array>::length() const
    {
        return this->m_array.length();
    }

    template <class Type, template <class> class Array>
    usize
    Vector<Type, Array>::size() const
    {
        return this->m_size;
    }

    template <class Type, template <class> class Array>
    bool
    Vector<Type, Array>::isFull() const
    {
        return this->m_size == this->length();
    }

    template <class Type, template <class> class Array>
    bool
    Vector<Type, Array>::isEmpty() const
    {
        return this->m_size == 0;
    }

    template <class Type, template <class> class Array>
    Array<Type>&
    Vector<Type, Array>::values()
    {
        return this->m_array;
    }

    template <class Type, template <class> class Array>
    const Array<Type>&
    Vector<Type, Array>::values() const
    {
        return this->m_array;
    }

    template <class Type, template <class> class Array>
    bool
    Vector<Type, Array>::insert(const Type& value, usize index)
    {
        auto& self = *this;

        if ( this->isFull() == true )
            this->resize(this->length() * 1.5f + 1);

        if ( this->isFull() == false ) {
            index = Math::min(index, this->m_size);

            this->m_size += 1;

            for ( usize i = this->m_size; i > index; i-- )
                self[i] = move(self[i - 1]);

            create(self[index], value);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    Vector<Type, Array>::insert(Type&& value, usize index)
    {
        auto& self = *this;

        if ( this->isFull() == true )
            this->resize(this->m_size * 1.5f + 1);

        if ( this->isFull() == false ) {
            index = Math::min(index, this->m_size);

            this->m_size += 1;

            for ( usize i = this->m_size; i > index; i-- )
                self[i] = move(self[i - 1]);

            create(self[index], move(value));

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    Vector<Type, Array>::remove(usize index)
    {
        auto& self = *this;

        if ( this->isEmpty() == false ) {
            index = Math::max(index, this->m_size - 1);

            this->m_size -= 1;

            for ( usize i = index; i < this->m_size - 1; i++ )
                self[i] = move(self[i + 1]);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    Vector<Type, Array>::resize(usize length)
    {
        return this->m_array.resize(length);
    }

    template <class Type, template <class> class Array>
    Type&
    Vector<Type, Array>::operator[](usize index)
    {
        return this->m_array[index];
    }

    template <class Type, template <class> class Array>
    const Type&
    Vector<Type, Array>::operator[](usize index) const
    {
        return this->m_array[index];
    }
} // namespace smal
