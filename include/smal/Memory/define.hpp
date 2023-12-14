#ifndef SMAL_MEMORY_DEFINE_HPP
#define SMAL_MEMORY_DEFINE_HPP

#include <smal/Memory/depend.hpp>

namespace ma
{
    class BaseOrigin;
    class NullOrigin;
    class ArenaOrigin;
    class PoolOrigin;

    template <class Item>
    class BaseBuffer;

    template <class Item>
    class SimpleBuffer;

    static const u32 g_kib = 1024;
    static const u32 g_mib = g_kib * g_kib;
    static const u32 g_gib = g_mib * g_kib;

    static const u32 g_kb = 1000;
    static const u32 g_mb = g_kb * g_kb;
    static const u32 g_gb = g_mb * g_kb;
} // namespace ma

#include <smal/Memory/util.hpp>

#endif // SMAL_MEMORY_DEFINE_HPP
