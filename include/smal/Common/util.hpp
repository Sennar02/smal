#ifndef SMAL_COMMON_HELPER_HPP
#define SMAL_COMMON_HELPER_HPP

#include <smal/Common/traits/RemoveRef.hpp>

namespace ma
{
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
    create(Type& value, Args... args);

    template <class Type>
    Type&
    destroy(Type& value);
} // namespace ma

#include <smal/Common/impl/util.tpp>

#endif // SMAL_COMMON_HELPER_HPP
