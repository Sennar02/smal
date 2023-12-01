#ifndef SMAL_MEMORY_ALLOC_PROXY_ALLOC_HPP
#define SMAL_MEMORY_ALLOC_PROXY_ALLOC_HPP

#include <smal/Memory/Alloc/BaseAlloc.hpp>

namespace ma
{
    class ProxyAlloc
        : public BaseAlloc
    {
    public:
        /**
         *
        */
        ProxyAlloc();

        /**
         *
         */
        ProxyAlloc(BaseAlloc& alloc);

    protected:
        /**
         *
         */
        BaseAlloc* m_alloc;
    };
} // namespace ma

#endif // SMAL_MEMORY_ALLOC_PROXY_ALLOC_HPP
