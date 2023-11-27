#include <smal/Memory/Origin.hpp>
#include <malloc.h>

namespace ma
{
    Origin::Origin(usize size)
        : m_memory {(char*) calloc(1, size)}
        , m_size {size}
    { }

    Origin::~Origin()
    {
        free(m_memory);
    }

    usize
    Origin::size() const
    {
        return m_size;
    }

    char*
    Origin::memory()
    {
        return m_memory;
    }

    const char*
    Origin::memory() const
    {
        return m_memory;
    }
} // namespace ma
