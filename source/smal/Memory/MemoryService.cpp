#include <smal/Memory/MemoryService.hpp>
#include <malloc.h>

namespace ma
{
    MemoryService::MemoryService(u32 size)
        : m_arena {calloc(1, size), size}
    { }

    MemoryService::~MemoryService()
    {
        char* memory = m_arena.memory();

        if ( memory != 0 )
            free(memory);
    }

    u32
    MemoryService::size() const
    {
        return m_arena.size();
    }

    char*
    MemoryService::memory()
    {
        return m_arena.memory();
    }

    const char*
    MemoryService::memory() const
    {
        return m_arena.memory();
    }
} // namespace ma
