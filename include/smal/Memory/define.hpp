#ifndef SMAL_MEMORY_DEFINE_HPP
#define SMAL_MEMORY_DEFINE_HPP

#include <smal/Memory/depend.hpp>

namespace ma
{
    class BaseAlloc;
    class PoolAlloc;
    class StackAlloc;

    class Memory;

    template <class Type>
    class FixedBuffer;

    static const usize g_KiB = 1024;
    static const usize g_MiB = g_KiB * g_KiB;
    static const usize g_GiB = g_MiB * g_KiB;

    static const usize g_KB = 1000;
    static const usize g_MB = g_KB * g_KB;
    static const usize g_GB = g_MB * g_KB;

    static const usize g_memory_size =
        g_GiB * 1;
} // namespace ma

#endif // SMAL_MEMORY_DEFINE_HPP
