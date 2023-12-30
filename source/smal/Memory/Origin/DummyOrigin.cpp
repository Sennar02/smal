#include <smal/Memory/Origin/DummyOrigin.hpp>

namespace ma
{
    DummyOrigin::DummyOrigin()
        : BaseOrigin()
    { }

    DummyOrigin::DummyOrigin(void* memory, u32 size)
        : BaseOrigin()
    { }

    bool
    DummyOrigin::availab(u32 size) const
    {
        return true;
    }

    bool
    DummyOrigin::prepare()
    {
        return true;
    }

    char*
    DummyOrigin::acquire(u32 size)
    {
        return (char*) calloc(1, size);
    }

    bool
    DummyOrigin::release(void* memory)
    {
        free(memory);

        return true;
    }
} // namespace ma
