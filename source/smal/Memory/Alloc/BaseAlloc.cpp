#include <smal/Memory/Alloc/BaseAlloc.hpp>

namespace ma
{
    BaseAlloc::BaseAlloc(void* memory, u32 size)
        : m_memory {(char*) memory}
        , m_size {size}
    {
        if ( memory == 0 )
            m_size = 0;
    }

    u32
    BaseAlloc::size() const
    {
        return m_size;
    }

    char*
    BaseAlloc::memory()
    {
        return m_memory;
    }

    const char*
    BaseAlloc::memory() const
    {
        return m_memory;
    }

    bool
    BaseAlloc::contains(void* memory)
    {
        char* addr = (char*) memory;

        if ( addr != 0 ) {
            return addr < m_memory + m_size &&
                   addr >= m_memory;
        }

        return true;
    }
} // namespace ma
