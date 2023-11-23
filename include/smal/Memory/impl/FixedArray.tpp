#include <smal/Memory/Array/FixedArray.hpp>

namespace ma
{
    template <class Type>
    FixedArray<Type>::FixedArray()
        : m_memory {0}
        , m_size {0}
    { }

    template <class Type>
    FixedArray<Type>::FixedArray(BaseOrigin* origin, usize size)
        : m_memory {0}
        , m_size {0}
    {
        Page page = origin->reserve(size * SIZE);

        if ( page.is_null() == false ) {
            m_memory = page.memory();
            m_size   = page.size();

            m_size /= SIZE;
        }
    }

    template <class Type>
    FixedArray<Type>::FixedArray(void* memory, usize size)
        : m_memory {(char*) memory}
        , m_size {size}
    { }

    template <class Type>
    FixedArray<Type>::~FixedArray()
    { }

    template <class Type>
    usize
    FixedArray<Type>::size() const
    {
        return m_size;
    }

    template <class Type>
    bool
    FixedArray<Type>::resize(usize size)
    {
        return false;
    }

    template <class Type>
    void
    FixedArray<Type>::clear()
    { }

    template <class Type>
    Type&
    FixedArray<Type>::operator[](usize index)
    {
        return (Type&) m_memory[index * SIZE];
    }

    template <class Type>
    const Type&
    FixedArray<Type>::operator[](usize index) const
    {
        return (Type&) m_memory[index * SIZE];
    }
} // namespace ma
