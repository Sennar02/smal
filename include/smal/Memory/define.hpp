#ifndef SMAL_MEMORY_DEFINE_HPP
#define SMAL_MEMORY_DEFINE_HPP

#include <smal/Memory/depend.hpp>

namespace ma
{
    static const u32 g_kib = 1024;
    static const u32 g_mib = g_kib * g_kib;
    static const u32 g_gib = g_mib * g_kib;

    static const u32 g_kb = 1000;
    static const u32 g_mb = g_kb * g_kb;
    static const u32 g_gb = g_mb * g_kb;

    class BaseAlloc;
    class NullAlloc;
    class PoolAlloc;
    class StackAlloc;
    class ArenaAlloc;
    class SplitAlloc;

    class PageTable;

    class MemoryModule;
} // namespace ma

#endif // SMAL_MEMORY_DEFINE_HPP
