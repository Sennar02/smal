#include <smal/Common/Tuple.hpp>
#include <smal/Common/impl/TupleHelp.hpp>

namespace smal
{
    template <class F, class... R>
    Tuple<F, R...>::Tuple()
        : impl::ITuple<F, R...>()
    { }

    template <class F, class... R>
    template <long I>
    auto&
    Tuple<F, R...>::get()
    {
        return impl::TupleHelp<I>::unwind(*this);
    }

    template <class F, class... R>
    template <long I>
    const auto&
    Tuple<F, R...>::get() const
    {
        return impl::TupleHelp<I>::unwind(*this);
    }
} // namespace smal
