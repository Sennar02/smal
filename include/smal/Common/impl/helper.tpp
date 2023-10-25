#include <smal/Common/helper.hpp>
#include <new>

namespace ma
{
    namespace Math
    {
        template <class Type>
        Type
        div(Type a, Type b)
        {
            if ( b == 0 )
                return b;

            return a / b;
        }

        template <class Type>
        Type
        mod(Type a, Type b)
        {
            if ( b == 0 )
                return b;

            return a % b;
        }

        template <class Type>
        Type
        floor(Type a, Type b)
        {
            return div(a, b);
        }

        template <class Type>
        Type
        ceil(Type a, Type b)
        {
            Type res = div(a, b);

            if ( mod(a, b) != 0 )
                return res + 1;

            return res;
        }

        template <class Type>
        Type
        min(Type a, Type b)
        {
            if ( a < b )
                return a;

            return b;
        }

        template <class Type>
        Type
        max(Type a, Type b)
        {
            if ( a < b )
                return b;

            return a;
        }

        template <class Type>
        Type
        abs(Type a)
        {
            if ( a < 0 )
                return -a;

            return a;
        }
    } // namespace Math

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

        value = move(other);
        other = move(temp);

        return value;
    }

    template <class Type>
    Type
    exch(Type& value, Type&& other)
    {
        Type temp = move(value);

        value = forw<Type>(other);

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
    create(Type& value, Args&&... args)
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
