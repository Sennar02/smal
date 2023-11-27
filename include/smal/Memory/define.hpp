#ifndef SMAL_MEMORY_DEFINE_HPP
#define SMAL_MEMORY_DEFINE_HPP

#include <smal/Memory/depend.hpp>

namespace ma
{
    static const usize g_KiB = 1024;
    static const usize g_MiB = g_KiB * g_KiB;
    static const usize g_GiB = g_MiB * g_KiB;

    static const usize g_KB = 1000;
    static const usize g_MB = g_KB * g_KB;
    static const usize g_GB = g_MB * g_KB;

    class BaseAlloc;
    class PoolAlloc;
    class StackAlloc;

    template <class Type>
    class Bucket;

    template <class Type>
    class Handle;

    template <class Type>
    class BaseBlock;

    template <class Type>
    class FixedBlock;

    template <class Type>
    class PagedBlock;

    class PageTable;
} // namespace ma

#endif // SMAL_MEMORY_DEFINE_HPP
