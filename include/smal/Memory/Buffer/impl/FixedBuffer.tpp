#include <smal/Memory/Buffer/FixedBuffer.hpp>

namespace ma
{
    template <class Type>
    FixedBuffer<Type>::FixedBuffer()
        : m_memory {0}
        , m_size {0}
    { }

    template <class Type>
    FixedBuffer<Type>::FixedBuffer(BaseAlloc& alloc, usize size)
        : m_memory {0}
        , m_size {0}
    {
        char* addr = alloc.acquire(g_type_size * size);

        if ( addr != 0 ) {
            m_memory = addr;
            m_size   = size / g_type_size;
        }
    }

    template <class Type>
    FixedBuffer<Type>::FixedBuffer(void* memory, usize size)
        : m_memory {(char*) memory}
        , m_size {size}
    { }

    template <class Type>
    FixedBuffer<Type>::~FixedBuffer()
    { }

    template <class Type>
    usize
    FixedBuffer<Type>::size() const
    {
        return m_size;
    }

    template <class Type>
    bool
    FixedBuffer<Type>::resize(usize size)
    {
        return false;
    }

    template <class Type>
    void
    FixedBuffer<Type>::clear()
    { }

    template <class Type>
    Type&
    FixedBuffer<Type>::operator[](usize index)
    {
        char* elem =
            &m_memory[g_type_size * index];

        return *(Type*) elem;
    }

    template <class Type>
    const Type&
    FixedBuffer<Type>::operator[](usize index) const
    {
        char* elem =
            &m_memory[g_type_size * index];

        return *(Type*) elem;
    }
} // namespace ma
