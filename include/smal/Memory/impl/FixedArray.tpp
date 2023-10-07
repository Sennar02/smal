#include <smal/Memory/FixedArray.hpp>

namespace smal
{
    template <class Type>
    FixedArray<Type>::FixedArray()
        : m_memory {0}
        , m_length {0}
    { }

    template <class Type>
    FixedArray<Type>::FixedArray(void* memory, long length)
        : m_memory {(Type*) memory}
        , m_length {length}
    { }

    template <class Type>
    FixedArray<Type>::~FixedArray()
    { }

    template <class Type>
    long
    FixedArray<Type>::length() const
    {
        return this->m_length;
    }

    template <class Type>
    bool
    FixedArray<Type>::resize(long length)
    {
        return false;
    }

    template <class Type>
    Type&
    FixedArray<Type>::operator[](long index)
    {
        return this->m_memory[index];
    }

    template <class Type>
    const Type&
    FixedArray<Type>::operator[](long index) const
    {
        return this->m_memory[index];
    }
} // namespace smal
