#include <smal/Memory/Handle.hpp>

namespace ma
{
    template <class Type>
    Handle<Type>::Handle(Bucket<Type>* bucket, char* memory)
        : m_bucket {bucket}
        , m_memory {memory}
    { }

    template <class Type>
    Handle<Type>::~Handle()
    {
        if ( m_bucket != 0 )
            m_bucket->release(*this);
    }

    template <class Type>
    bool
    Handle<Type>::is_null() const
    {
        return m_memory == 0;
    }

    template <class Type>
    char*
    Handle<Type>::memory()
    {
        return m_memory;
    }

    template <class Type>
    const char*
    Handle<Type>::memory() const
    {
        return m_memory;
    }

    template <class Type>
    Type&
    Handle<Type>::item()
    {
        return *(Type*) m_memory;
    }

    template <class Type>
    const Type&
    Handle<Type>::item() const
    {
        return *(Type*) m_memory;
    }
} // namespace ma
