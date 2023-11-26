#include <smal/Memory/Memory.hpp>

namespace ma
{
    Memory::Memory(usize size)
        : m_alloc {calloc(1, size), size}
    { }

    Memory::~Memory()
    {
        free(m_alloc.memory());
    }
} // namespace ma
