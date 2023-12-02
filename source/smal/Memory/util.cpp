#include <smal/Memory/util.hpp>

namespace ma
{
    char*
    memorySet(void* memory, u32 size, char byte)
    {
        char* buffer = (char*) memory;

        for ( u32 i = 0; i < size; i++ )
            buffer[i] = byte;

        return buffer;
    }
} // namespace ma
