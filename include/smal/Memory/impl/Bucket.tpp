#include <smal/Memory/Bucket.hpp>

namespace ma
{
    template <class Type>
    Bucket<Type>::Bucket(void* memory, usize size)
        : PoolAlloc(memory, size, s_type_size)
    { }

    template <class Type>
    Handle<Type>
    Bucket<Type>::acquire()
    {
        return {this, PoolAlloc::acquire()};
    }

    template <class Type>
    bool
    Bucket<Type>::release(Handle<Type>& handle)
    {
        bool result = false;

        if ( PoolAlloc::release(handle.memory()) )
            handle = {0, 0}, result = true;

        return result;
    }
} // namespace ma
