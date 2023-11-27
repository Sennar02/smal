#include <smal/Memory/Block/FixedBlock.hpp>

namespace ma
{
    template <class Type>
    FixedBlock<Type>::FixedBlock()
        : m_memory {0}
        , m_size {0}
    { }

    template <class Type>
    FixedBlock<Type>::FixedBlock(BaseAlloc& alloc, usize size)
        : m_memory {0}
        , m_size {0}
    {
        char* addr = alloc.acquire(s_type_size * size);

        if ( addr != 0 ) {
            m_memory = addr;
            m_size   = size / s_type_size;
        }
    }

    template <class Type>
    FixedBlock<Type>::FixedBlock(void* memory, usize size)
        : m_memory {(char*) memory}
        , m_size {size}
    { }

    template <class Type>
    FixedBlock<Type>::~FixedBlock()
    { }

    template <class Type>
    usize
    FixedBlock<Type>::size() const
    {
        return m_size;
    }

    template <class Type>
    bool
    FixedBlock<Type>::resize(usize size)
    {
        return false;
    }

    template <class Type>
    void
    FixedBlock<Type>::clear()
    { }

    template <class Type>
    Type&
    FixedBlock<Type>::operator[](usize index)
    {
        char* elem =
            &m_memory[s_type_size * index];

        return *(Type*) elem;
    }

    template <class Type>
    const Type&
    FixedBlock<Type>::operator[](usize index) const
    {
        char* elem =
            &m_memory[s_type_size * index];

        return *(Type*) elem;
    }
} // namespace ma
