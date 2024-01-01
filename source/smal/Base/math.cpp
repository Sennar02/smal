#include <smal/Base/math.hpp>

namespace ma
{
    template <>
    u32
    hash(const char& value)
    {
        return value;
    }

    template <>
    u32
    hash(const unsigned char& value)
    {
        return value;
    }

    template <>
    u32
    hash(const short& value)
    {
        return value;
    }

    template <>
    u32
    hash(const unsigned short& value)
    {
        return value;
    }

    template <>
    u32
    hash(const int& value)
    {
        return value;
    }

    template <>
    u32
    hash(const unsigned int& value)
    {
        return value;
    }

    template <>
    u32
    hash(const long& value)
    {
        return value;
    }

    template <>
    u32
    hash(const unsigned long& value)
    {
        return value;
    }

    template <>
    u32
    hash(const long long& value)
    {
        return value;
    }

    template <>
    u32
    hash(const unsigned long long& value)
    {
        return value;
    }

    template <>
    u32
    hash(char* const& value)
    {
        const char* str = value;
        u32         res = 5381;

        while ( u8 chr = *str++ ) {
            res = (res << 5) + res;
            res = res ^ chr;
        }

        return res;
    }

    template <>
    u32
    hash(const char* const& value)
    {
        const char* str = value;
        u32         res = 5381;

        while ( u8 chr = *str++ ) {
            res = (res << 5) + res;
            res = res ^ chr;
        }

        return res;
    }
} // namespace ma
