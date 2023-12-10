#ifndef SMAL_BASE_TRAITS_SIGNATURE_HPP
#define SMAL_BASE_TRAITS_SIGNATURE_HPP

#include <smal/Base/traits/declared.hpp>

namespace ma
{
    namespace impl
    {
        template <class Ret, class... Args>
        auto
        signature(Ret (*)(Args...))
            -> Ret (*)(Args...);

        template <class Ret, class... Args, class... Rest>
        auto
        signature(Ret (*)(Args...), Rest...)
            -> Ret (*)(Args...);

        template <class Type, class Ret, class... Args>
        auto
        signature(Ret (Type::*)(Args...))
            -> Ret (*)(Args...);

        template <class Type, class Ret, class... Args, class... Rest>
        auto
        signature(Ret (Type::*)(Args...), Rest...)
            -> Ret (*)(Args...);

        template <class Type, class Ret, class... Args>
        auto
        signature(Ret (Type::*)(Args...) const)
            -> Ret (*)(Args...);

        template <class Type, class Ret, class... Args, class... Rest>
        auto
        signature(Ret (Type::*)(Args...) const, Rest...)
            -> Ret (*)(Args...);

        template <class Type, class Ret, class... Rest>
        auto
        signature(Ret Type::*, Rest...)
            -> Ret (*)();

        template <class... Func>
        struct Signature
        {
            using Main = decltype(signature(declared<Func>()...));
        };
    } // namespace impl

    template <auto Func>
    using Signature = RemovePtr<typename impl::Signature<decltype(Func)>::Main>;
} // namespace ma

#endif // SMAL_BASE_TRAITS_SIGNATURE_HPP
