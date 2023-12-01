#ifndef SMAL_MEMORY_DEFINE_HPP
#define SMAL_MEMORY_DEFINE_HPP

#include <smal/Memory/depend.hpp>

namespace ma
{
    static const u32 g_KiB = 1024;
    static const u32 g_MiB = g_KiB * g_KiB;
    static const u32 g_GiB = g_MiB * g_KiB;

    static const u32 g_KB = 1000;
    static const u32 g_MB = g_KB * g_KB;
    static const u32 g_GB = g_MB * g_KB;

    class MemoryService;

    class BaseAlloc;
    class NullAlloc;
    class PoolAlloc;
    class StackAlloc;
    class ProxyAlloc;

    template <class... Allocs>
    class ChainAlloc;

    template <class Type>
    class BaseBlock;

    template <class Type>
    class FixedBlock;

    template <class Type>
    class PagedBlock;

    class PageTable;
} // namespace ma

#endif // SMAL_MEMORY_DEFINE_HPP
