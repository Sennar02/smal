#include <smal/Memory/Alloc/ProxyAlloc.hpp>

namespace ma
{
    ProxyAlloc::ProxyAlloc()
        : m_alloc {0}
    { }

    ProxyAlloc::ProxyAlloc(BaseAlloc& alloc)
        : m_alloc {&alloc}
    { }
} // namespace ma
