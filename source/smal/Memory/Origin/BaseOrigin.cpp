#include <smal/Memory/Origin/BaseOrigin.hpp>

namespace ma
{
    BaseOrigin::BaseOrigin()
        : m_memory {0}
        , m_size {0}
    { }

    BaseOrigin::BaseOrigin(void* memory, u32 size)
        : BaseOrigin()
    {
        char* addr = (char*) memory;

        if ( memory != 0 && size != 0 ) {
            m_memory = addr;
            m_size   = size;
        }
    }

    const char*
    BaseOrigin::memory() const
    {
        return m_memory;
    }

    u32
    BaseOrigin::size() const
    {
        return m_size;
    }

    bool
    BaseOrigin::contains(void* memory) const
    {
        char* inf = m_memory;
        char* sup = m_memory + m_size;
        char* ptr = (char*) memory;

        return inf <= ptr && ptr < sup;
    }
} // namespace ma
