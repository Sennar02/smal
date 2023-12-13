#include <smal/Memory/MemoryModule.hpp>

#include <malloc.h> // calloc, free

namespace ma
{
    MemoryModule::MemoryModule(u32 size, u32 page)
        : m_table {calloc(size, page), size * page, page}
    { }

    MemoryModule::~MemoryModule()
    {
        while ( m_table.isEmpty() == false )
            free(m_table.pull());
    }
} // namespace ma
