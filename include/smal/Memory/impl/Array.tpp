#include <smal/Memory/Array.hpp>

namespace smal
{
    template <class Type>
    Array<Type>::Array(void* memory, long length)
        : m_memory {(Type*) memory}
        , m_length {length}
    { }

    template <class Type>
    Array<Type>::~Array()
    { }

    template <class Type>
    long
    Array<Type>::length() const
    {
        return this->m_length;
    }

    template <class Type>
    bool
    Array<Type>::resize(long length)
    {
        return false;
    }

    template <class Type>
    Type&
    Array<Type>::operator[](long index)
    {
        return this->m_memory[index];
    }

    template <class Type>
    const Type&
    Array<Type>::operator[](long index) const
    {
        return this->m_memory[index];
    }
} // namespace smal
