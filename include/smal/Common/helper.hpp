#ifndef SMAL_COMMON_HELPER_HPP
#define SMAL_COMMON_HELPER_HPP

#include <smal/Common/define.hpp>

namespace ma
{
    namespace impl
    {
        template <class Type>
        struct RemoveRef
        {
            using Result = Type;
        };

        template <class Type>
        struct RemoveRef<Type&>
        {
            using Result = Type;
        };

        template <class Type>
        struct RemoveRef<Type&&>
        {
            using Result = Type;
        };

        template <class Type>
        struct RemovePtr
        {
            using Result = Type;
        };

        template <class Type>
        struct RemovePtr<Type*>
        {
            using Result = Type;
        };

        template <class Ret, class... Args>
        auto
        funcType(Ret (*)(Args...)) -> Ret (*)(Args...)
        { }

        template <class Ret, class... Args, class... Rest>
        auto
        funcType(Ret (*)(Args...), Rest...) -> Ret (*)(Args...)
        { }

        template <class Type, class Ret, class... Args>
        auto
        funcType(Ret (Type::*)(Args...)) -> Ret (*)(Args...)
        { }

        template <class Type, class Ret, class... Args, class... Rest>
        auto
        funcType(Ret (Type::*)(Args...), Rest...) -> Ret (*)(Args...)
        { }

        template <class Type, class Ret, class... Args>
        auto
        funcType(Ret (Type::*)(Args...) const) -> Ret (*)(Args...)
        { }

        template <class Type, class Ret, class... Args, class... Rest>
        auto
        funcType(Ret (Type::*)(Args...) const, Rest...) -> Ret (*)(Args...)
        { }

        template <class Type, class Ret, class... Rest>
        auto
        funcType(Ret Type::*, Rest...) -> Ret (*)()
        { }

        template <class... Func>
        struct FuncType
        {
        private:
            using Decl = decltype(funcType(std::declval<Func>()...));

        public:
            using Result = typename RemovePtr<Decl>::Result;
        };
    } // namespace impl

    template <class Type>
    using RemoveRef = typename impl::RemoveRef<Type>::Result;

    template <class Type>
    using RemovePtr = typename impl::RemovePtr<Type>::Result;

    template <class... Func>
    using FuncType = typename impl::FuncType<Func...>::Result;

    namespace Math
    {
        template <class Type>
        Type
        div(Type a, Type b);

        template <class Type>
        Type
        mod(Type a, Type b);

        template <class Type>
        Type
        floor(Type a, Type b);

        template <class Type>
        Type
        ceil(Type a, Type b);

        template <class Type>
        Type
        min(Type a, Type b);

        template <class Type>
        Type
        max(Type a, Type b);

        template <class Type>
        Type
        abs(Type a);

        template <class Type>
        usize
        hash(const Type& value);
    } // namespace Math

    template <class Type>
    RemoveRef<Type>&&
    move(Type&& value);

    template <class Type>
    Type&&
    forw(RemoveRef<Type>& value);

    template <class Type>
    Type&&
    forw(RemoveRef<Type>&& value);

    template <class Type>
    Type&
    swap(Type& value, Type& other);

    template <class Type>
    Type
    exch(Type& value, Type&& other);

    template <class Type>
    Type&
    create(Type& value);

    template <class Type, class... Args>
    Type&
    create(Type& value, Args&&... args);

    template <class Type>
    Type&
    destroy(Type& value);
} // namespace ma

#include <smal/Common/impl/helper.tpp>

#endif // SMAL_COMMON_HELPER_HPP
