#ifndef SMAL_BASE_HELPER_HPP
#define SMAL_BASE_HELPER_HPP

#include <smal/Base/traits/RemoveRef.hpp>

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

    template <class Type, class... Args>
    void
    ctor(Type& value, Args&&... args);

    template <class Type>
    void
    dtor(Type& value);
} // namespace ma

#include <smal/Base/inline/util.inl>

#endif // SMAL_BASE_HELPER_HPP
