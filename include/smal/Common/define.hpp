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

    template <class>
    class Func;
} // namespace ma

#endif // SMAL_COMMON_DEFINE_HPP
