#include <smal/Memory/Alloc/NullAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    NullAlloc::NullAlloc()
    { }

    NullAlloc::NullAlloc(void* memory, u32 size)
    { }

    u32
    NullAlloc::avail() const
    {
        return 0;
    }

    bool
    NullAlloc::prepare()
    {
        return true;
    }

    char*
    NullAlloc::acquire(u32 size)
    {
        return 0;
    }

    bool
    NullAlloc::release(void* memory)
    {
        return true;
    }

    bool
    NullAlloc::release()
    {
        return true;
    }
} // namespace ma
