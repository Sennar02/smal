#include <smal/Json/JsonReader.hpp>

namespace ma
{
    JsonReader::JsonReader(u32 depth)
        : m_lexer {}
        , m_depth {depth}
    { }
} // namespace ma
