#include <smal/Memory/define.hpp>

namespace smal::Memory
{
    void
    set(void* memory, usize length, char value)
    {
        char* dst = (char*) memory;

        for ( usize i = 0; i < length; i++ )
            dst[i] = value;
    }
} // namespace smal::Memory
