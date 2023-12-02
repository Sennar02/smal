#include <smal/Memory/Alloc/ChainAlloc.hpp>

namespace ma
{
    ChainAlloc<>::ChainAlloc()
    { }

    u32
    ChainAlloc<>::avail() const
    {
        return 0;
    }

    bool
    ChainAlloc<>::prepare()
    {
        return true;
    }

    char*
    ChainAlloc<>::acquire(u32 size)
    {
        return 0;
    }

    bool
    ChainAlloc<>::release(void* memory)
    {
        if ( memory == 0 )
            return true;

        return false;
    }

    bool
    ChainAlloc<>::release()
    {
        return true;
    }
} // namespace ma
