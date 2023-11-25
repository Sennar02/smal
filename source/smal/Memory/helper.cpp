#include <smal/Memory/helper.hpp>

namespace ma
{
    void*
    memory_set(void* memory, usize size, char byte)
    {
        for ( usize i = 0; i < size; i++ )
            ((char*) memory)[i] = byte;

        return memory;
    }
} // namespace ma
