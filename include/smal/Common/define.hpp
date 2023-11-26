#ifndef SMAL_COMMON_DEFINE_HPP
#define SMAL_COMMON_DEFINE_HPP

#include <smal/Common/depend.hpp>

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

    static const usize g_max_u8    = (usize) UINT8_MAX;
    static const usize g_max_u16   = (usize) UINT16_MAX;
    static const usize g_max_u32   = (usize) UINT32_MAX;
    static const usize g_max_u64   = (usize) UINT64_MAX;
    static const usize g_max_usize = (usize) SIZE_MAX;

    static const isize g_max_i8    = (isize) (g_max_u8 / 2);
    static const isize g_max_i16   = (isize) (g_max_u16 / 2);
    static const isize g_max_i32   = (isize) (g_max_u32 / 2);
    static const isize g_max_i64   = (isize) (g_max_u64 / 2);
    static const isize g_max_isize = (isize) (g_max_usize / 2);

    static const usize g_min_u8    = (usize) 0;
    static const usize g_min_u16   = (usize) 0;
    static const usize g_min_u32   = (usize) 0;
    static const usize g_min_u64   = (usize) 0;
    static const usize g_min_usize = (usize) 0;

    static const isize g_min_i8    = (isize) (-g_max_i8 - 1);
    static const isize g_min_i16   = (isize) (-g_max_i16 - 1);
    static const isize g_min_i32   = (isize) (-g_max_i32 - 1);
    static const isize g_min_i64   = (isize) (-g_max_i64 - 1);
    static const isize g_min_isize = (isize) (-g_max_isize - 1);

    static const f64 g_inf = INFINITY;
    static const f64 g_nan = NAN;

    class String;

    class FileIStream;
    class FileOStream;
    class FileReader;
    class FileWriter;

    template <class>
    class Function;

    template <auto>
    class Bind
    {
    public:
        Bind() = default;
    };

    template <auto Func>
    inline static const Bind<Func>
        bind = {};
} // namespace ma

#endif // SMAL_COMMON_DEFINE_HPP
