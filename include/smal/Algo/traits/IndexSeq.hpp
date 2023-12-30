#ifndef SMAL_ALGO_TRAITS_SEQUENCE_HPP
#define SMAL_ALGO_TRAITS_SEQUENCE_HPP

#include <smal/Algo/define.hpp>

namespace ma
{
    namespace impl
    {
        template <u32...>
        struct IndexSeq
        { };

        template <u32 Count, u32... List>
        struct IndexGen
            : public IndexGen<Count - 1, Count - 1, List...>
        { };

        template <u32... List>
        struct IndexGen<0, List...>
        {
            using Main = IndexSeq<List...>;
        };
    } // namespace impl

    template <u32... List>
    using IndexSeq = impl::IndexSeq<List...>;

    template <u32 Count, u32... List>
    using IndexGen = typename impl::IndexGen<Count, List...>::Main;
} // namespace ma

#endif // SMAL_ALGO_TRAITS_SEQUENCE_HPP
