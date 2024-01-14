#include <smal/Memory/util.hpp>

namespace ma
{
    template <class Type>
    Type*
    acquire(BaseOrigin& origin, u32 count)
    {
        static const u32 s_size = sizeof(Type);

        u32   size = s_size * count;
        void* addr = origin.acquire(size);

        return (Type*) addr;
    }

    template <class Type>
    bool
    release(BaseOrigin& origin, Type* memory)
    {
        return origin.release(memory);
    }
} // namespace ma
