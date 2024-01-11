#include <smal/Memory/util.hpp>

namespace ma
{
    template <class Type, class... Args>
    Type*
    acquire(BaseOrigin& origin, Args&&... args)
    {
        static const u32 s_size = sizeof(Type);

        Type* addr = (Type*) origin.acquire(s_size);

        if ( addr != 0 )
            ctor(*addr, forw<Args>(args)...);

        return addr;
    }

    template <class Type>
    bool
    release(BaseOrigin& origin, Type* memory)
    {
        return origin.release(memory);
    }
} // namespace ma
