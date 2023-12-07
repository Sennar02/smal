#include <smal/Json/JsonReader.hpp>
#include <smal/Json/JsonClient.hpp>

namespace ma
{
    JsonReader::JsonReader(u32 depth)
        : m_lexer {}
        , m_client {0}
        , m_depth {depth}
    { }

    JsonReader::JsonReader(JsonClient& client, u32 depth)
        : m_lexer {}
        , m_client {&client}
        , m_depth {depth}
    { }

    bool
    JsonReader::bind(JsonClient& client)
    {
        m_client = &client;

        return true;
    }

    bool
    JsonReader::read(const String& json)
    {
        if ( m_lexer.bind(json) )
            return send(m_lexer.next());

        return false;
    }

    bool
    JsonReader::send(const JsonToken& token, u32 depth)
    {
        if ( depth < m_depth ) {
            switch ( token.type ) {
                case Type::DictLPar: return dict(depth);
                case Type::ListLPar: return list(depth);
                case Type::String: return string(token);
                case Type::Number: return number(token);
                case Type::Boolean: return boolean(token);
                case Type::Null: return null(token);

                default:
                    break;
            }
        }

        return false;
    }

    bool
    JsonReader::string(const JsonToken& token)
    {
        return m_client->string(token);
    }

    bool
    JsonReader::number(const JsonToken& token)
    {
        const char* memory = token.memory();
        f32         number = 0;

        if ( token.flag & Flag::Float ) {
            number = strtod(memory, 0);

            if ( number == (i32) number )
                return m_client->number((i32) number);

            if ( number == (u32) number )
                return m_client->number((u32) number);

            return m_client->number(number);
        }

        if ( token.flag & Flag::Negat )
            return m_client->number((i32) strtol(memory, 0, 10));

        return m_client->number((u32) strtoul(memory, 0, 10));
    }

    bool
    JsonReader::boolean(const JsonToken& token)
    {
        if ( token.memory()[0] == 't' )
            return m_client->boolean(true);

        return m_client->boolean(false);
    }

    bool
    JsonReader::null(const JsonToken& token)
    {
        return m_client->null();
    }

    bool
    JsonReader::dict(u32 depth)
    {
        JsonToken token;
        u32       count = 0;

        if ( m_client->dictEnter(depth) == false )
            return true;

        for ( count = 0; true; count++ ) {
            token = m_lexer.next();

            if ( token.type == Type::DictRPar )
                break;

            if ( token.type == Type::String ) {
                if ( m_client->dictProp(token) == false )
                    return true;
            } else
                return false;

            token = m_lexer.next();

            if ( token.type == Type::Colon ) {
                token = m_lexer.next();

                if ( send(token, depth + 1) == false )
                    return false;
            } else
                return false;

            token = m_lexer.next();

            if ( token.type == Type::Comma ) continue;
            if ( token.type == Type::DictRPar ) break;

            return false;
        }

        if ( m_client->dictLeave(depth, count) == false )
            return true;

        return true;
    }

    bool
    JsonReader::list(u32 depth)
    {
        JsonToken token;
        u32       count = 0;

        if ( m_client->listEnter(depth) == false )
            return true;

        for ( count = 0; true; count++ ) {
            token = m_lexer.next();

            if ( token.type != Type::ListRPar ) {
                if ( send(token, depth + 1) == false )
                    return false;
            } else
                break;

            token = m_lexer.next();

            if ( token.type == Type::Comma ) continue;
            if ( token.type == Type::ListRPar ) break;

            return false;
        }

        if ( m_client->listLeave(depth, count) == false )
            return true;

        return true;
    }

} // namespace ma
