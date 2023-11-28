#ifndef SMAL_MEMORY_ALLOC_PROXY_ALLOC_HPP
#define SMAL_MEMORY_ALLOC_PROXY_ALLOC_HPP

#include <smal/Memory/define.hpp>

namespace ma
{
    template <class Alloc>
    class ProxyAlloc
        : public Alloc
    {
    public:
        /**
         *
         */
        template <class Other, class... Args>
        ProxyAlloc(const Other& other, Args&&... args);
    };
} // namespace ma

#include <smal/Memory/Alloc/impl/ProxyAlloc.tpp>

#endif // SMAL_MEMORY_ALLOC_PROXY_ALLOC_HPP
