#include <smal/Memory/Alloc/BaseAlloc.hpp>

namespace ma
{
    BaseAlloc::BaseAlloc(void* memory, usize size)
        : m_memory {(char*) memory}
        , m_size {size}
    { }

    usize
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
    BaseAlloc::contains(void* addr)
    {
        char* memory = (char*) addr;

        return memory >= m_memory &&
               memory < m_memory + m_size;
    }
} // namespace ma
