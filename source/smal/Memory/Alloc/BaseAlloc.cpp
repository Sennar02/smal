#include <smal/Memory/Alloc/BaseAlloc.hpp>

namespace ma
{
    BaseAlloc::BaseAlloc()
        : m_memory {0}
        , m_size {0}
    { }

    BaseAlloc::BaseAlloc(void* memory, u32 size)
        : BaseAlloc()
    {
        char* addr = (char*) memory;

        if ( memory != 0 && size != 0 ) {
            m_memory = addr;
            m_size   = size;
        }
    }

    char*
    BaseAlloc::memory() const
    {
        return m_memory;
    }

    u32
    BaseAlloc::size() const
    {
        return m_size;
    }

    bool
    BaseAlloc::contains(void* memory) const
    {
        char* addr = (char*) memory;
        char* inf  = m_memory;
        char* sup  = m_memory + m_size;

        return inf <= addr && addr < sup;
    }
} // namespace ma
