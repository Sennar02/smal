#ifndef SMAL_BASE_MATH_HPP
#define SMAL_BASE_MATH_HPP

#include <smal/Base/define.hpp>

namespace ma
{
    template <class Type>
    u32
    hash(const Type& value);

    template <class Type, class Other>
    Type
    max(Type left, Other right);

    template <class Type, class Other>
    Type
    min(Type left, Other right);
} // namespace ma

#include <smal/Base/inline/math.inl>

#endif // SMAL_BASE_MATH_HPP
