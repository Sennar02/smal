#include <smal/Memory/util.hpp>

namespace ma
{
    void*
    memsum(void* memory, i32 offset)
    {
        char* addr = (char*) memory;

        if ( addr != 0 )
            return (void*) (addr + offset);

        return 0;
    }
} // namespace ma
