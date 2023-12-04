#include <smal/Memory/Block/FixedBlock.hpp>

namespace ma
{
    template <class Type>
    FixedBlock<Type>::FixedBlock()
        : m_memory {0}
        , m_size {0}
    { }

    template <class Type>
    FixedBlock<Type>::FixedBlock(BaseAlloc& alloc, u32 size)
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
    u32
    FixedBlock<Type>::size() const
    {
        return m_size;
    }

    template <class Type>
    bool
    FixedBlock<Type>::resize(u32 size)
    {
        return false;
    }

    template <class Type>
    Type&
    FixedBlock<Type>::find(u32 index) const
    {
        return (Type&) m_memory[index * s_type_size];
    }

    template <class Type>
    Type&
    FixedBlock<Type>::operator[](u32 index) const
    {
        return find(index);
    }
} // namespace ma
