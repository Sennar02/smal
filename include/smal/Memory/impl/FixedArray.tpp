#include <smal/Memory/Array/FixedArray.hpp>

namespace smal
{
    template <class Type>
    FixedArray<Type>::FixedArray()
        : m_memory {0}
        , m_length {0}
    { }

    template <class Type>
    FixedArray<Type>::FixedArray(BaseOrigin* origin, usize length)
        : m_memory {0}
        , m_length {0}
    {
        Part page = origin->reserve(length * SIZE);

        if ( page.isNull() == false ) {
            this->m_memory = page.memory();
            this->m_length = page.length();

            this->m_length /= SIZE;
        }
    }

    template <class Type>
    FixedArray<Type>::FixedArray(void* memory, usize length)
        : m_memory {(char*) memory}
        , m_length {length}
    { }

    template <class Type>
    FixedArray<Type>::~FixedArray()
    { }

    template <class Type>
    usize
    FixedArray<Type>::length() const
    {
        return this->m_length;
    }

    template <class Type>
    bool
    FixedArray<Type>::resize(usize length)
    {
        return false;
    }

    template <class Type>
    Type&
    FixedArray<Type>::operator[](usize index)
    {
        return (Type&) this->m_memory[index * SIZE];
    }

    template <class Type>
    const Type&
    FixedArray<Type>::operator[](usize index) const
    {
        return (Type&) this->m_memory[index * SIZE];
    }
} // namespace smal
