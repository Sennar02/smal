#ifndef SMAL_COMMON_TRAITS_FUNC_SIGNAT_HPP
#define SMAL_COMMON_TRAITS_FUNC_SIGNAT_HPP

#include <smal/Common/traits/declared.hpp>

namespace ma
{
    namespace impl
    {
        template <class Ret, class... Args>
        auto
        func_signat(Ret (*)(Args...)) -> Ret (*)(Args...)
        { }

        template <class Ret, class... Args, class... Rest>
        auto
        func_signat(Ret (*)(Args...), Rest...) -> Ret (*)(Args...)
        { }

        template <class Type, class Ret, class... Args>
        auto
        func_signat(Ret (Type::*)(Args...)) -> Ret (*)(Args...)
        { }

        template <class Type, class Ret, class... Args, class... Rest>
        auto
        func_signat(Ret (Type::*)(Args...), Rest...) -> Ret (*)(Args...)
        { }

        template <class Type, class Ret, class... Args>
        auto
        func_signat(Ret (Type::*)(Args...) const) -> Ret (*)(Args...)
        { }

        template <class Type, class Ret, class... Args, class... Rest>
        auto
        func_signat(Ret (Type::*)(Args...) const, Rest...) -> Ret (*)(Args...)
        { }

        template <class Type, class Ret, class... Rest>
        auto
        func_signat(Ret Type::*, Rest...) -> Ret (*)()
        { }

        template <class... Func>
        struct FuncSignat
        {
            using Main = decltype(func_signat(declared<Func>()...));
        };
    } // namespace impl

    template <class... Func>
    using FuncSignat = RemovePtr<typename impl::FuncSignat<Func...>::Main>;
} // namespace ma

#endif // SMAL_COMMON_TRAITS_FUNC_SIGNAT_HPP
