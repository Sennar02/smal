#include <smal/Json/JsonToken.hpp>

namespace ma
{
    JsonToken::JsonToken()
        : String()
        , type {Type::Error}
        , flag {0}
    { }

    JsonToken::JsonToken(const char* memory, u32 size, Type type, u32 flag)
        : String(memory, size)
        , type {type}
        , flag {flag}
    { }
} // namespace ma
