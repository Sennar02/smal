#include <smal/Memory/Origin/NullOrigin.hpp>

namespace ma
{
    NullOrigin::NullOrigin()
        : BaseOrigin()
    { }

    NullOrigin::NullOrigin(void* memory, u32 size)
        : BaseOrigin()
    { }

    bool
    NullOrigin::availab(u32 size) const
    {
        return size == 0;
    }

    bool
    NullOrigin::prepare()
    {
        return true;
    }

    char*
    NullOrigin::acquire(u32 size)
    {
        return 0;
    }

    bool
    NullOrigin::release(void* memory)
    {
        return memory == 0;
    }
} // namespace ma
