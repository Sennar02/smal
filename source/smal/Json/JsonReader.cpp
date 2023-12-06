#include <smal/Json/JsonReader.hpp>
#include <smal/Json/Handler/BaseHandler.hpp>

namespace ma
{
    JsonReader::JsonReader(u32 depth)
        : m_lexer {}
        , m_hndlr {0}
        , m_depth {depth}
    { }

    JsonReader::JsonReader(u32 depth, BaseHandler& handler)
        : m_lexer {}
        , m_hndlr {&handler}
        , m_depth {depth}
    { }

    bool
    JsonReader::bind(BaseHandler& handler)
    {
        m_hndlr = &handler;

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
                case Type::DictLPar: return object(depth);
                case Type::ListLPar: return array(depth);
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
        return m_hndlr->string(token);
    }

    bool
    JsonReader::number(const JsonToken& token)
    {
        const char* memory = token.memory();
        f32         number = 0;

        if ( token.flag & Flag::Float ) {
            number = strtod(memory, 0);

            if ( number == (i32) number )
                return m_hndlr->number((i32) number);

            if ( number == (u32) number )
                return m_hndlr->number((u32) number);

            return m_hndlr->number(number);
        }

        if ( token.flag & Flag::Negat )
            return m_hndlr->number((i32) strtol(memory, 0, 10));

        return m_hndlr->number((u32) strtoul(memory, 0, 10));
    }

    bool
    JsonReader::boolean(const JsonToken& token)
    {
        if ( token.memory()[0] == 't' )
            return m_hndlr->boolean(true);

        return m_hndlr->boolean(false);
    }

    bool
    JsonReader::null(const JsonToken& token)
    {
        return m_hndlr->null();
    }

    bool
    JsonReader::object(u32 depth)
    {
        JsonToken token;
        u32       count = 0;

        if ( m_hndlr->dictEnter(depth) == false )
            return true;

        for ( count = 0; true; count++ ) {
            token = m_lexer.next();

            if ( token.type == Type::DictRPar )
                break;

            if ( token.type == Type::String ) {
                if ( m_hndlr->dictProp(token) == false )
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

        if ( m_hndlr->dictLeave(depth, count) == false )
            return true;

        return true;
    }

    bool
    JsonReader::array(u32 depth)
    {
        JsonToken token;
        u32       count = 0;

        if ( m_hndlr->listEnter(depth) == false )
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

        if ( m_hndlr->listLeave(depth, count) == false )
            return true;

        return true;
    }

} // namespace ma
