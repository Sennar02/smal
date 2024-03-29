#include <smal/Memory/OriginFactory.hpp>

namespace ma
{
    template <class Origin, class... Args>
    Origin
    OriginFactory::request(u32 size, Args&&... args)
    {
        char* addr = 0;

        if ( m_table.isFull() == false ) {
            addr = (char*) calloc(1u, size);

            if ( m_table.insert(addr) )
                return {addr, size, forw<Args>(args)...};
        }

        return {};
    }
} // namespace ma
