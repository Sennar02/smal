#include <smal/Memory/util.hpp>

namespace ma
{
    char*
    memoryWipe(void* memory, u32 size)
    {
        char* addr = (char*) memory;

        for ( u32 i = 0; i < size; i++ )
            addr[i] = 0;

        return addr;
    }
} // namespace ma
