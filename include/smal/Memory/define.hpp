#ifndef SMAL_MEMORY_DEFINE_HPP
#define SMAL_MEMORY_DEFINE_HPP

#include <smal/Memory/depend.hpp>

namespace ma
{
    class PageTable;
    class OriginFactory;

    class BaseOrigin;
    class NullOrigin;
    class ArenaOrigin;
    class StackOrigin;
    class PoolOrigin;
    class SplitOrigin;
    class DummyOrigin;

    class FixedLayout;
    class PagedLayout;

    template <class Item, class Layout>
    class Array;

    static const u32 g_kib = 1024u;
    static const u32 g_mib = g_kib * g_kib;
    static const u32 g_gib = g_mib * g_kib;

    static const u32 g_kb = 1000u;
    static const u32 g_mb = g_kb * g_kb;
    static const u32 g_gb = g_mb * g_kb;

    extern SplitOrigin g_origin;
} // namespace ma

#endif // SMAL_MEMORY_DEFINE_HPP
