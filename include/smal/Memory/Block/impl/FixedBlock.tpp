#include <smal/Memory/Block/FixedBlock.hpp>

namespace ma
{
    template <class Type>
    FixedBlock<Type>::FixedBlock()
        : m_memory {0}
        , m_size {0}
    { }

    template <class Type>
    FixedBlock<Type>::FixedBlock(const BaseAlloc& alloc, u32 size)
        : m_memory {0}
        , m_size {0}
    {
        auto& alias = (BaseAlloc&) alloc;
        char* addr  = alias.acquire(s_type_size * size);

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
    FixedBlock<Type>::operator[](u32 index)
    {
        char* elem =
            &m_memory[s_type_size * index];

        return *(Type*) elem;
    }

    template <class Type>
    const Type&
    FixedBlock<Type>::operator[](u32 index) const
    {
        char* elem =
            &m_memory[s_type_size * index];

        return *(Type*) elem;
    }
} // namespace ma
