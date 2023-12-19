#include <smal/Memory/MemoryModule.hpp>

namespace ma
{
    static const u32 s_node_size =
        MemoryTable::s_node_size;

    MemoryModule::MemoryModule(u32 size)
        : m_table {}
    {
        char* addr = (char*) calloc(1u, size * s_node_size);

        if ( addr != 0 )
            m_table = {addr, size};
    }

    MemoryModule::~MemoryModule()
    {
        while ( m_table.isEmpty() == false )
            free(m_table.remove());
    }
} // namespace ma
