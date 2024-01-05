#ifndef SMAL_BASE_DEFINE_HPP
#define SMAL_BASE_DEFINE_HPP

#include <smal/Base/depend.hpp>

namespace ma
{
    using u8  = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    using i8  = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;

    using f32 = float_t;
    using f64 = double_t;

    using usize = size_t;
    using isize = ssize_t;

    static const u8    g_max_u8    = UINT8_MAX;
    static const u16   g_max_u16   = UINT16_MAX;
    static const u32   g_max_u32   = UINT32_MAX;
    static const u64   g_max_u64   = UINT64_MAX;
    static const usize g_max_usize = SIZE_MAX;

    static const u8    g_min_u8    = 0;
    static const u16   g_min_u16   = 0;
    static const u32   g_min_u32   = 0;
    static const u64   g_min_u64   = 0;
    static const usize g_min_usize = 0;

    static const i8    g_max_i8    = g_max_u8 / 2;
    static const i16   g_max_i16   = g_max_u16 / 2;
    static const i32   g_max_i32   = g_max_u32 / 2;
    static const i64   g_max_i64   = g_max_u64 / 2;
    static const isize g_max_isize = g_max_usize / 2;

    static const i8    g_min_i8    = -g_max_i8 - 1;
    static const i16   g_min_i16   = -g_max_i16 - 1;
    static const i32   g_min_i32   = -g_max_i32 - 1;
    static const i64   g_min_i64   = -g_max_i64 - 1;
    static const isize g_min_isize = -g_max_isize - 1;

    static const f64 g_inf = INFINITY;
    static const f64 g_nan = NAN;

    class String;
} // namespace ma

#endif // SMAL_BASE_DEFINE_HPP
