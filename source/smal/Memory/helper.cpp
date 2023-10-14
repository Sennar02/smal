#include <smal/Memory/define.hpp>

namespace smal::Memory
{
    void
    set(void* memory, usize length, char byte)
    {
        char* dst = (char*) memory;

        for ( usize i = 0; i < length; i++ )
            dst[i] = byte;
    }
} // namespace smal::Memory
