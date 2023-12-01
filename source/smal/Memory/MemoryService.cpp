#include <smal/Memory/MemoryService.hpp>
#include <malloc.h>

namespace ma
{
    MemoryService::MemoryService(u32 size)
        : m_stack {calloc(1, size), size}
    { }

    MemoryService::~MemoryService()
    {
        char* memory = m_stack.memory();

        if ( memory != 0 )
            free(memory);
    }

    u32
    MemoryService::size() const
    {
        return m_stack.size();
    }

    char*
    MemoryService::memory()
    {
        return m_stack.memory();
    }

    const char*
    MemoryService::memory() const
    {
        return m_stack.memory();
    }
} // namespace ma
