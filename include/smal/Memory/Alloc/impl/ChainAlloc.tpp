#include <smal/Memory/Alloc/ChainAlloc.hpp>

namespace ma
{
    template <class Alloc, class... Rest>
    ChainAlloc<Alloc, Rest...>::ChainAlloc()
    { }

    template <class Alloc, class... Rest>
    ChainAlloc<Alloc, Rest...>::ChainAlloc(const Alloc& alloc, const Rest&... rest)
        : m_alloc {alloc}
        , m_rest {rest...}
    { }

    template <class Alloc, class... Rest>
    template <u32 Index>
    auto&
    ChainAlloc<Alloc, Rest...>::alloc()
    {
        if constexpr ( Index != 0 )
            return m_rest.template alloc<Index - 1>();
        else
            return m_alloc;
    }

    template <class Alloc, class... Rest>
    template <u32 Index>
    const auto&
    ChainAlloc<Alloc, Rest...>::alloc() const
    {
        if constexpr ( Index != 0 )
            return m_rest.template alloc<Index - 1>();
        else
            return m_alloc;
    }

    template <class Alloc, class... Rest>
    u32
    ChainAlloc<Alloc, Rest...>::avail() const
    {
        return m_alloc.avail() + m_rest.avail();
    }

    template <class Alloc, class... Rest>
    bool
    ChainAlloc<Alloc, Rest...>::prepare()
    {
        if ( m_alloc.prepare() )
            return m_rest.prepare();

        return false;
    }

    template <class Alloc, class... Rest>
    char*
    ChainAlloc<Alloc, Rest...>::acquire(u32 size)
    {
        char* addr =
            m_alloc.acquire(size);

        if ( addr == 0 )
            return m_rest.acquire(size);

        return addr;
    }

    template <class Alloc, class... Rest>
    bool
    ChainAlloc<Alloc, Rest...>::release(void* memory)
    {
        if ( m_alloc.release(memory) )
            return true;

        return m_rest.release(memory);
    }

    template <class Alloc, class... Rest>
    bool
    ChainAlloc<Alloc, Rest...>::release()
    {
        if ( m_alloc.release() )
            return m_rest.release();

        return false;
    }

    ChainAlloc<>::ChainAlloc()
    { }

    u32
    ChainAlloc<>::avail() const
    {
        return 0;
    }

    bool
    ChainAlloc<>::prepare()
    {
        return true;
    }

    char*
    ChainAlloc<>::acquire(u32 size)
    {
        return 0;
    }

    bool
    ChainAlloc<>::release(void* memory)
    {
        if ( memory == 0 )
            return true;

        return false;
    }

    bool
    ChainAlloc<>::release()
    {
        return true;
    }
} // namespace ma
