#include <smal/Struct/Vector.hpp>

namespace smal
{
    using namespace Common;

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
    long
    Vector<Type, Array>::length() const
    {
        return this->m_array.length();
    }

    template <class Type, template <class> class Array>
    long
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
    Vector<Type, Array>::insert(const Type& value, long index)
    {
        auto& self = *this;

        if ( index < 0 ) index = this->m_size;

        if ( this->isFull() )
            this->resize(this->size() * 1.5f + 10);

        if ( this->isFull() == false ) {
            this->m_size += 1;

            for ( long i = this->m_size; i > index; i-- )
                self[i] = move(self[i - 1]);

            create(self[index], value);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    Vector<Type, Array>::insert(Type&& value, long index)
    {
        auto& self = *this;

        if ( index < 0 ) index = this->m_size;

        if ( this->isFull() )
            this->resize(this->size() * 1.5f + 10);

        if ( this->isFull() == false ) {
            this->m_size += 1;

            for ( long i = this->m_size; i > index; i-- )
                self[i] = move(self[i - 1]);

            create(self[index], move(value));

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    Vector<Type, Array>::remove(long index)
    {
        auto& self = *this;

        if ( index < 0 )
            index = this->m_size + index;

        if ( this->isEmpty() == false ) {
            this->m_size -= 1;

            for ( long i = index; i < this->m_size - 1; i++ )
                self[i] = move(self[i + 1]);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Array>
    bool
    Vector<Type, Array>::resize(long length)
    {
        return this->m_array.resize(length);
    }

    template <class Type, template <class> class Array>
    Type&
    Vector<Type, Array>::operator[](long index)
    {
        if ( index < 0 )
            index = this->m_size + index;

        return this->m_array[index];
    }

    template <class Type, template <class> class Array>
    const Type&
    Vector<Type, Array>::operator[](long index) const
    {
        if ( index < 0 )
            index = this->m_size + index;

        return this->m_array[index];
    }
} // namespace smal
