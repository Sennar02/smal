#include <smal/Parser/Json/Client.hpp>

namespace ma::Json
{
    Client::~Client()
    { }

    bool
    Client::string(const char* string, usize length)
    {
        return true;
    }

    bool
    Client::number(usize value)
    {
        return true;
    }

    bool
    Client::number(isize value)
    {
        return true;
    }

    bool
    Client::number(f64 value)
    {
        return true;
    }

    bool
    Client::boolean(bool value)
    {
        return true;
    }

    bool
    Client::null()
    {
        return true;
    }

    bool
    Client::name(const char* string, usize length)
    {
        return true;
    }

    bool
    Client::array_start(usize depth)
    {
        return true;
    }

    bool
    Client::array_stop(usize depth, usize count)
    {
        return true;
    }

    bool
    Client::object_start(usize depth)
    {
        return true;
    }

    bool
    Client::object_stop(usize depth, usize count)
    {
        return true;
    }
} // namespace ma::Json
