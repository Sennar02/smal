#include <smal/Common/math.hpp>

namespace ma
{
    f64
    floor(usize num, usize den)
    {
        return num / den;
    }

    f64
    ceil(usize num, usize den)
    {
        return num / den + 1;
    }

    template <>
    usize
    hash(const char& value)
    {
        return value;
    }

    template <>
    usize
    hash(const unsigned char& value)
    {
        return value;
    }

    template <>
    usize
    hash(const short& value)
    {
        return value;
    }

    template <>
    usize
    hash(const unsigned short& value)
    {
        return value;
    }

    template <>
    usize
    hash(const int& value)
    {
        return value;
    }

    template <>
    usize
    hash(const unsigned int& value)
    {
        return value;
    }

    template <>
    usize
    hash(const long& value)
    {
        return value;
    }

    template <>
    usize
    hash(const unsigned long& value)
    {
        return value;
    }

    template <>
    usize
    hash(const long long& value)
    {
        return value;
    }

    template <>
    usize
    hash(const unsigned long long& value)
    {
        return value;
    }

    template <>
    usize
    hash(char* const& value)
    {
        const char* str = value;
        usize       res = 5381;

        while ( u8 chr = *str++ ) {
            res = (res << 5) + res;
            res = res ^ chr;
        }

        return res;
    }

    template <>
    usize
    hash(const char* const& value)
    {
        const char* str = value;
        usize       res = 5381;

        while ( u8 chr = *str++ ) {
            res = (res << 5) + res;
            res = res ^ chr;
        }

        return res;
    }
} // namespace ma
