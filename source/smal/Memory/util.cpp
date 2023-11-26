#include <smal/Memory/util.hpp>

namespace ma
{
    char*
    memory_set(void* memory, usize size, char byte)
    {
        char* buffer = (char*) memory;

        for ( usize i = 0; i < size; i++ )
            buffer[i] = byte;

        return buffer;
    }
} // namespace ma
