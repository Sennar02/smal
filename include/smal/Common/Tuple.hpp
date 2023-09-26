#ifndef SMAL_COMMON_TUPLE_HPP
#define SMAL_COMMON_TUPLE_HPP

#include <smal/Common/define.hpp>
#include <smal/Common/impl/TupleHelp.hpp>

namespace smal
{
    template <class First, class... Rest>
    class Tuple<First, Rest...>
        : private impl::ITuple<First, Rest...>
    {
    public:
        static const long LENGTH = sizeof...(Rest) + 1;

    public:
        /**
         * @brief
         */
        Tuple();

        /**
         * @brief
         *
         * @tparam Index
         * @return auto&
         */
        template <long Index>
        auto&
        get();

        /**
         * @brief
         *
         * @tparam Index
         * 
         * @return const auto&
         */
        template <long Index>
        const auto&
        get() const;
    };
} // namespace smal

#include <smal/Common/impl/Tuple.tpp>

#endif // SMAL_COMMON_TUPLE_HPP
