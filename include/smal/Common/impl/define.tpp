#include <smal/Common/define.hpp>

namespace smal::Math
{
    template <class Type>
    Type
    div(Type a, Type b)
    {
        if ( b == 0 )
            return b;

        return a / b;
    }
} // namespace smal::Math
