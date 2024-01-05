#include <smal/Base/math.hpp>

namespace ma
{
    template <class Type, class Other>
    Type
    max(Type left, Other right)
    {
        Type help = (Type) right;

        if ( left < help )
            return help;

        return left;
    }

    template <class Type, class Other>
    Type
    min(Type left, Other right)
    {
        Type help = (Type) right;

        if ( left <= help )
            return left;

        return help;
    }
} // namespace ma
