#include <smal/Common/File.hpp>

namespace ma
{
    template <class Func>
    File&
    File::open(FileMode mode, Func oper, String name)
    {
        if ( open(mode, name).is_open(mode) )
            oper(*this);

        return *this;
    }

    template <class Func>
    File&
    File::close(Func oper)
    {
        if ( is_open() )
            oper(*this);

        return close();
    }

    template <class Func>
    File&
    File::call(FileMode mode, Func oper, String name)
    {
        if ( open(mode, name).is_open(mode) )
            oper(*this);

        return close();
    }
} // namespace ma
