#include <smal/Algo/Tuple.hpp>

namespace ma
{
    template <class Type, class... Rest>
    Tuple<Type, Rest...>::Tuple()
    { }

    template <class Type, class... Rest>
    Tuple<Type, Rest...>::Tuple(const Type& value, const Rest&... rest)
        : m_value {value}
        , m_tail {rest...}
    { }

    template <class Type, class... Rest>
    Tuple<Type, Rest...>::Tuple(const Type& value, const Tuple<Rest...>& rest)
        : m_value {value}
        , m_tail {rest}
    { }

    template <class Type, class... Rest>
    template <u32 Index>
    auto&
    Tuple<Type, Rest...>::extract()
    {
        if constexpr ( Index != 0 )
            return m_tail.template extract<Index - 1>();
        else
            return m_value;
    }

    template <class Type, class... Rest>
    template <u32 Index>
    const auto&
    Tuple<Type, Rest...>::extract() const
    {
        if constexpr ( Index != 0 )
            return m_tail.template extract<Index - 1>();
        else
            return m_value;
    }
} // namespace ma
