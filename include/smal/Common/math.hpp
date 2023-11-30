#ifndef SMAL_COMMON_MATH_HPP
#define SMAL_COMMON_MATH_HPP

#include <smal/Common/define.hpp>

namespace ma
{
    f32
    floor(f32 num, f32 den);

    f32
    ceil(f32 num, f32 den);

    template <class Type>
    u32
    hash(const Type& value);
} // namespace ma

#endif // SMAL_COMMON_MATH_HPP
