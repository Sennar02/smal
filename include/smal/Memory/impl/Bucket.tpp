#include <smal/Memory/Bucket.hpp>

namespace ma
{
    template <class Type>
    Bucket<Type>::Bucket(void* memory, usize size)
        : PageAlloc(memory, size, s_type_size)
    { }

    template <class Type>
    Handle<Type>
    Bucket<Type>::acquire()
    {
        return {this, PageAlloc::acquire()};
    }

    template <class Type>
    bool
    Bucket<Type>::release(Handle<Type>& handle)
    {
        bool result = false;

        if ( PageAlloc::release(handle.memory()) )
            handle = {0, 0}, result = true;

        return result;
    }
} // namespace ma
