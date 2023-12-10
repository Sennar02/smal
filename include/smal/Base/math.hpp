#ifndef SMAL_BASE_MATH_HPP
#define SMAL_BASE_MATH_HPP

#include <smal/Base/define.hpp>

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

#endif // SMAL_BASE_MATH_HPP
