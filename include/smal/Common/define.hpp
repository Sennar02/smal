#ifndef SMAL_COMMON_DEFINE_HPP
#define SMAL_COMMON_DEFINE_HPP

namespace smal
{
    namespace Math
    {
        /**
         * @brief
         *
         * @tparam Type
         *
         * @param a
         * @param b
         *
         * @return Type
         */
        template <class Type>
        Type
        div(Type a, Type b);
    } // namespace Math

    template <class... Types>
    class Tuple;

    template <>
    class Tuple<>
    {
    public:
        static const long LENGTH = 0;
    };
} // namespace smal

#include <smal/Common/impl/define.tpp>

#endif // SMAL_COMMON_DEFINE_HPP
