#ifndef SMAL_COMMON_HELPER_HPP
#define SMAL_COMMON_HELPER_HPP

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
    } // namespace impl

    template <class Type>
    using RemoveRef = typename impl::RemoveRef<Type>::Result;

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
