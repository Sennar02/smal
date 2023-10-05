#include <smal/Struct/Vector.hpp>

namespace smal
{
    template <class Type, template <class> class Arr>
    Vector<Type, Arr>::Vector()
        : m_array {}
        , m_size {0}
    { }

    template <class Type, template <class> class Arr>
    Vector<Type, Arr>::Vector(const Arr<Type>& array)
        : m_array {Common::move(array)}
        , m_size {0}
    { }

    template <class Type, template <class> class Arr>
    Vector<Type, Arr>::~Vector()
    { }

    template <class Type, template <class> class Arr>
    long
    Vector<Type, Arr>::length() const
    {
        return this->m_array.length();
    }

    template <class Type, template <class> class Arr>
    long
    Vector<Type, Arr>::size() const
    {
        return this->m_size;
    }

    template <class Type, template <class> class Arr>
    bool
    Vector<Type, Arr>::isFull() const
    {
        return this->m_size == this->length();
    }

    template <class Type, template <class> class Arr>
    bool
    Vector<Type, Arr>::isEmpty() const
    {
        return this->m_size == 0;
    }

    template <class Type, template <class> class Arr>
    bool
    Vector<Type, Arr>::insert(const Type& value, long index)
    {
        auto& self = *this;

        if ( index == -1 )
            index = this->m_size;

        if ( this->isFull() == false ) {
            for ( long i = this->m_size; i > index; i-- )
                self[i] = Common::move(self[i - 1]);

            Common::create(self[index], value);

            this->m_size += 1;
            return true;
        }

        return false;
    }

    template <class Type, template <class> class Arr>
    bool
    Vector<Type, Arr>::insert(Type&& value, long index)
    {
        auto& self = *this;

        if ( index == -1 )
            index = this->m_size;

        if ( this->isFull() == false ) {
            for ( long i = this->m_size; i > index; i-- )
                self[i] = Common::move(self[i - 1]);

            Common::create(self[index], Common::move(value));

            this->m_size += 1;
            return true;
        }

        return false;
    }

    template <class Type, template <class> class Arr>
    bool
    Vector<Type, Arr>::remove(long index)
    {
        auto& self = *this;

        if ( index == -1 )
            index = this->m_size - 1;

        if ( this->isEmpty() == false ) {
            for ( long i = index; i < this->m_size - 1; i++ )
                self[i] = Common::move(self[i + 1]);

            this->m_size -= 1;
            return true;
        }

        return false;
    }

    template <class Type, template <class> class Arr>
    bool
    Vector<Type, Arr>::resize(long length)
    {
        return this->m_array.resize(length);
    }

    template <class Type, template <class> class Arr>
    Type&
    Vector<Type, Arr>::access(long index)
    {
        if ( index == -1 )
            index = this->m_size - 1;

        return this->m_array[index];
    }

    template <class Type, template <class> class Arr>
    const Type&
    Vector<Type, Arr>::access(long index) const
    {
        if ( index == -1 )
            index = this->m_size - 1;

        return this->m_array[index];
    }

    template <class Type, template <class> class Arr>
    Type&
    Vector<Type, Arr>::operator[](long index)
    {
        return this->m_array[index];
    }

    template <class Type, template <class> class Arr>
    const Type&
    Vector<Type, Arr>::operator[](long index) const
    {
        return this->m_array[index];
    }
} // namespace smal
