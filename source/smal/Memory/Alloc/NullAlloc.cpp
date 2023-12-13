#include <smal/Memory/Alloc/NullAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    NullAlloc::NullAlloc()
        : BaseAlloc()
    { }

    NullAlloc::NullAlloc(void* memory, u32 size)
        : BaseAlloc()
    { }

    bool
    NullAlloc::availab(u32 size) const
    {
        return size == 0;
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
        return memory == 0;
    }
} // namespace ma
