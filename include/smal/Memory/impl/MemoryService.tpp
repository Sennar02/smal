#include <smal/Memory/MemoryService.hpp>

namespace ma
{
    template <class Alloc, class... Args>
    Alloc
    MemoryService::create(u32 size, Args&&... args)
    {
        char* addr =
            m_arena.acquire(size);

        return {addr, size, forw<Args>(args)...};
    }
} // namespace ma
