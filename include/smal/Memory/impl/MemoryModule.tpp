#include <smal/Memory/MemoryModule.hpp>

namespace ma
{
    template <class Origin, class... Args>
    bool
    MemoryModule::request(Origin& origin, u32 size, Args&&... args)
    {
        char* addr = 0;

        if ( m_table.isFull() == false ) {
            addr = (char*) calloc(1u, size);

            if ( m_table.insert(addr) )
                origin = {addr, size, forw<Args>(args)...};
        }

        return origin.memory() == addr;
    }
} // namespace ma
