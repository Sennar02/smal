#include <smal/Common/util.hpp>
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

    template <class Type>
    Type&
    create(Type& value)
    {
        new (&value)
            Type {};

        return value;
    }

    template <class Type, class... Args>
    Type&
    create(Type& value, Args... args)
    {
        new (&value)
            Type {forw<Args>(args)...};

        return value;
    }

    template <class Type>
    Type&
    destroy(Type& value)
    {
        value.~Type();

        return value;
    }
} // namespace ma
