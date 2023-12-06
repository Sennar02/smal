#include <smal/Json/JsonLexer.hpp>

namespace ma
{
    static String g_spaces = " \t\n\r";
    static String g_string = "\"\'";
    static String g_number = "+-.eE0123456789";
    static String g_float  = ".eE";
    static String g_negat  = "-";

    JsonLexer::JsonLexer()
        : m_json {}
    { }

    JsonLexer::JsonLexer(const String& json)
        : m_json {json}
    { }

    bool
    JsonLexer::bind(const String& json)
    {
        m_json = json;

        return true;
    }

    JsonToken
    JsonLexer::next()
    {
        const char* memory = m_json.memory();
        u32         length = m_json.size();
        u32         dist   = 0;
        char        byte   = 0;

        for ( ; true; dist++ ) {
            byte = memory[dist];

            if ( g_spaces.contains(byte) == false )
                break;
        }

        m_json = {
            memory + dist,
            length - dist,
        };

        return send(byte);
    }

    JsonToken
    JsonLexer::send(char byte)
    {
        switch ( byte ) {
            case '\"': return string('\"');
            case '\'': return string('\'');

            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': return number();

            case 't': return symbol("true", Type::Boolean);
            case 'f': return symbol("false", Type::Boolean);
            case 'n': return symbol("null", Type::Null);

            case '{': return symbol("{", Type::DictLPar);
            case '}': return symbol("}", Type::DictRPar);
            case '[': return symbol("[", Type::ListLPar);
            case ']': return symbol("]", Type::ListRPar);
            case ':': return symbol(":", Type::Colon);
            case ',': return symbol(",", Type::Comma);

            case '\0': return symbol("", Type::Finish);

            default:
                break;
        }

        return {};
    }

    JsonToken
    JsonLexer::string(char quot)
    {
        const char* memory = m_json.memory();
        u32         length = m_json.size();
        u32         dist   = 0;
        char        byte   = 0;

        if ( memory[dist++] != quot )
            return {};

        for ( ; true; dist++ ) {
            byte = memory[dist];

            if ( g_string.contains(byte) || byte == 0 )
                break;
        }

        if ( memory[dist++] != quot )
            return {};

        m_json = {
            memory + dist,
            length - dist,
        };

        return {memory + 1, dist - 2, Type::String};
    }

    JsonToken
    JsonLexer::number()
    {
        const char* memory = m_json.memory();
        u32         length = m_json.size();
        u32         dist   = 0;
        u32         flag   = 0;
        char        byte   = 0;

        for ( ; true; dist++ ) {
            byte = memory[dist];

            if ( g_float.contains(byte) ) flag |= Flag::Float;
            if ( g_negat.contains(byte) ) flag |= Flag::Negat;

            if ( g_number.contains(byte) == false )
                break;
        }

        m_json = {
            memory + dist,
            length - dist,
        };

        return {memory, dist, Type::Number, flag};
    }

    JsonToken
    JsonLexer::symbol(const String& symbol, JsonToken::Type type)
    {
        const char* memory = m_json.memory();
        u32         length = m_json.size();
        u32         dist   = symbol.size();

        if ( symbol.equals(m_json) ) {
            m_json = {
                memory + dist,
                length - dist,
            };
        } else
            return {};

        return {memory, dist, type};
    }
} // namespace ma
