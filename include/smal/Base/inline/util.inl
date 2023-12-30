#include <smal/Base/util.hpp>
#include <new>

namespace ma
{
    template <class Type>
    RemoveRef<Type>&&
    move(Type&& value)
    {
        return (RemoveRef<Type>&&) value;
    }

    template <class Type>
    Type&&
    forw(RemoveRef<Type>& value)
    {
        return (Type&&) value;
    }

    template <class Type>
    Type&&
    forw(RemoveRef<Type>&& value)
    {
        return (Type&&) value;
    }

    template <class Type>
    Type&
    swap(Type& value, Type& other)
    {
        Type temp = move(value);
        value     = move(other);
        other     = move(temp);

        return value;
    }

    template <class Type>
    Type
    exch(Type& value, Type&& other)
    {
        Type temp = move(value);
        value     = forw<Type>(other);

        return temp;
    }

    template <class Type, class... Args>
    void
    ctor(Type& value, Args&&... args)
    {
        new (&value) Type {forw<Args>(args)...};
    }

    template <class Type>
    void
    dtor(Type& value)
    {
        value.~Type();
    }
} // namespace ma
