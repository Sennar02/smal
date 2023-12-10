#include <smal/Memory/util.hpp>

namespace ma
{
    template <class Type, class Alloc>
    Type*
    acquire(Alloc& alloc)
    {
        Type* addr =
            (Type*) alloc.acquire(sizeof(Type));

        if ( addr != 0 ) create(*addr);

        return addr;
    }

    template <class Type, class Alloc, class... Args>
    Type*
    acquire(Alloc& alloc, Args&&... args)
    {
        Type* addr =
            (Type*) alloc.acquire(sizeof(Type));

        if ( addr != 0 )
            create(*addr, forw<Args>(args)...);

        return addr;
    }

    template <class Type, class Alloc>
    bool
    release(Alloc& alloc, Type* addr)
    {
        return alloc.release(addr);
    }
} // namespace ma
