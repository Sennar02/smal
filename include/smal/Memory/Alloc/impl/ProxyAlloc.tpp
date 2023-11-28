#include <smal/Memory/Alloc/ProxyAlloc.hpp>

namespace ma
{
    template <class Alloc>
    template <class Other, class... Args>
    ProxyAlloc<Alloc>::ProxyAlloc(const Other& other, Args&&... args)
        : Alloc((char*) other.memory(), other.size(), forw<Args>(args)...)
    { }
} // namespace ma
