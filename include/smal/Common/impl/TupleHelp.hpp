#ifndef SMAL_COMMON_IMPL_TUPLE_HELP_HPP
#define SMAL_COMMON_IMPL_TUPLE_HELP_HPP

namespace smal::impl
{
    template <class... T>
    struct ITuple;

    template <>
    struct ITuple<>
    { };

    template <class F, class... R>
    struct ITuple<F, R...>
    {
        F            first;
        ITuple<R...> rest;
    };

    template <long I>
    struct TupleHelp
    {
        template <class F, class... R>
        static auto&
        unwind(ITuple<F, R...>& tuple)
        {
            return TupleHelp<I - 1>::unwind(tuple.rest);
        }

        template <class F, class... R>
        static const auto&
        unwind(const ITuple<F, R...>& tuple)
        {
            return TupleHelp<I - 1>::unwind(tuple.rest);
        }
    };

    template <>
    struct TupleHelp<0>
    {
        template <class F, class... R>
        static F&
        unwind(ITuple<F, R...>& tuple)
        {
            return tuple.first;
        }

        template <class F, class... R>
        static const F&
        unwind(const ITuple<F, R...>& tuple)
        {
            return tuple.first;
        }
    };
} // namespace smal::impl

#endif // SMAL_COMMON_IMPL_TUPLE_HELP_HPP
