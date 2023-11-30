#include <smal/Memory/Bucket.hpp>

namespace ma
{
    template <class Type>
    Bucket<Type>::Bucket()
        : m_alloc {}
    { }

    template <class Type>
    Bucket<Type>::Bucket(void* memory, u32 size)
        : m_alloc {memory, size, s_type_size}
    { }

    template <class Type>
    Type*
    Bucket<Type>::acquire()
    {
        return (Type*) m_alloc.acquire();
    }

    template <class Type>
    bool
    Bucket<Type>::release(Type* addr)
    {
        return m_alloc.release(addr);
    }
} // namespace ma
