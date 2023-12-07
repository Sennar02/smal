#include <smal/Json/JsonClient.hpp>

namespace ma
{
    bool
    JsonClient::string(const String value)
    {
        return true;
    }

    bool
    JsonClient::number(u32 value)
    {
        return true;
    }

    bool
    JsonClient::number(i32 value)
    {
        return true;
    }

    bool
    JsonClient::number(f32 value)
    {
        return true;
    }

    bool
    JsonClient::boolean(bool value)
    {
        return true;
    }

    bool
    JsonClient::null()
    {
        return true;
    }

    bool
    JsonClient::listEnter(u32 depth)
    {
        return true;
    }

    bool
    JsonClient::listLeave(u32 depth, u32 count)
    {
        return true;
    }

    bool
    JsonClient::dictEnter(u32 depth)
    {
        return true;
    }

    bool
    JsonClient::dictProp(const String prop)
    {
        return true;
    }

    bool
    JsonClient::dictLeave(u32 depth, u32 count)
    {
        return true;
    }
} // namespace ma
