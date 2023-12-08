#include <smal/Memory/util.hpp>

namespace ma
{
    template <class Value, class Alloc>
    Value*
    acquire(Alloc& alloc)
    {
        Value* addr =
            (Value*) alloc.acquire(sizeof(Value));

        if ( addr != 0 ) create(*addr);

        return addr;
    }

    template <class Value, class Alloc, class... Args>
    Value*
    acquire(Alloc& alloc, Args&&... args)
    {
        Value* addr =
            (Value*) alloc.acquire(sizeof(Value));

        if ( addr != 0 )
            create(*addr, forw<Args>(args)...);

        return addr;
    }

    template <class Value, class Alloc>
    bool
    release(Alloc& alloc, Value* value)
    {
        return alloc.release(value);
    }
} // namespace ma
