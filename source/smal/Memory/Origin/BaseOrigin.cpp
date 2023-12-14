#include <smal/Memory/Origin/BaseOrigin.hpp>

namespace ma
{
    BaseOrigin::BaseOrigin()
        : m_memory {0}
        , m_size {0}
    { }

    BaseOrigin::BaseOrigin(const SimpleBuffer<char>& buffer)
        : BaseOrigin()
    {
        m_memory = buffer.memory();
        m_size   = buffer.size();
    }

    BaseOrigin::BaseOrigin(void* memory, u32 size)
        : BaseOrigin(SimpleBuffer<char> {memory, size})
    { }

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
