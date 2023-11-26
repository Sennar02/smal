
#include <smal/Memory/Memory.hpp>

namespace ma
{
    template <class Alloc>
    Alloc
    Memory::create(usize size)
    {
        return {m_alloc.acquire(size), size};
    }

    template <class Alloc>
    Alloc
    Memory::create(usize size, usize page)
    {
        return {m_alloc.acquire(size), size, page};
    }
} // namespace ma
