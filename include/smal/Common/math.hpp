#ifndef SMAL_COMMON_MATH_HPP
#define SMAL_COMMON_MATH_HPP

#include <smal/Common/define.hpp>

namespace ma
{
    f64
    floor(f64 num, f64 den);

    f64
    ceil(f64 num, f64 den);

    template <class Type>
    usize
    hash(const Type& value);
} // namespace ma

#endif // SMAL_COMMON_MATH_HPP
