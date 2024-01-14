#include <smal/Memory/Layout/FixedLayout.hpp>

namespace ma
{
    FixedLayout::FixedLayout(void* memory, u32 items, u32 scale)
        : m_memory {0}
        , m_length {0}
    {
        if ( memory != 0 && items * scale != 0 ) {
            m_memory = (char*) memory;
            m_length = items * scale;
        }
    }

    FixedLayout::FixedLayout(BaseOrigin& origin, u32 items, u32 scale)
        : FixedLayout(acquire<char>(origin, items * scale), items, scale)
    { }

    char*
    FixedLayout::memory() const
    {
        return m_memory;
    }

    u32
    FixedLayout::length(u32 scale) const
    {
        return m_length / scale;
    }

    bool
    FixedLayout::resize(u32 items, u32 scale)
    {
        return false;
    }

    char&
    FixedLayout::find(u32 index, u32 scale) const
    {
        return m_memory[index * scale];
    }
} // namespace ma
