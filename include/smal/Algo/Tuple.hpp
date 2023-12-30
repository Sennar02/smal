#ifndef SMAL_ALGO_TUPLE_HPP
#define SMAL_ALGO_TUPLE_HPP

#include <smal/Algo/define.hpp>

namespace ma
{
    template <>
    class Tuple<>
    {
    public:
        /**
         *
         */
        static const u32 s_size = 0;
    };

    template <class Type, class... Rest>
    class Tuple<Type, Rest...>
    {
    public:
        /**
         *
         */
        static const u32 s_size =
            Tuple<Rest...>::s_size + 1;

    public:
        /**
         *
         */
        Tuple();

        /**
         *
         */
        Tuple(const Type& value, const Rest&... rest);

        /**
         *
         */
        Tuple(const Type& value, const Tuple<Rest...>& rest);

        /**
         *
         */
        template <u32 Index>
        auto&
        extract();

        /**
         *
         */
        template <u32 Index>
        const auto&
        extract() const;

    private:
        /**
         *
         */
        Type m_value;

        /**
         *
         */
        Tuple<Rest...> m_tail;
    };

    template <class... Args>
    Tuple(const Args&...)
        -> Tuple<Args...>;

    template <class Type, class... Rest>
    Tuple(const Type&, const Tuple<Rest...>&)
        -> Tuple<Type, Rest...>;
} // namespace ma

#include <smal/Algo/inline/Tuple.inl>

#endif // SMAL_ALGO_TUPLE_HPP
