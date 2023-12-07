#include <smal/Json/JsonReader.hpp>

namespace ma
{
    template <class User>
    bool
    JsonReader::read(User& user, const String& json)
    {
        if ( m_lexer.bind(json) )
            return deduce(user, m_lexer.next());

        return false;
    }

    template <class User>
    bool
    JsonReader::deduce(User& user, const JsonToken& token, u32 depth)
    {
        if ( depth < m_depth ) {
            switch ( token.type ) {
                case Type::String: return string(user, token);
                case Type::Number: return number(user, token);
                case Type::Boolean: return boolean(user, token);
                case Type::Null: return null(user, token);
                case Type::ObjLPar: return object(user, depth);
                case Type::ArrLPar: return array(user, depth);

                default:
                    break;
            }
        }

        return false;
    }

    template <class User>
    bool
    JsonReader::string(User& user, const JsonToken& token)
    {
        return user.string(token);
    }

    template <class User>
    bool
    JsonReader::number(User& user, u32 value)
    {
        return user.number(value);
    }

    template <class User>
    bool
    JsonReader::number(User& user, i32 value)
    {
        return user.number(value);
    }

    template <class User>
    bool
    JsonReader::number(User& user, f32 value)
    {
        if ( value == (u32) value )
            return user.number((u32) value);

        if ( value == (i32) value )
            return user.number((i32) value);

        return user.number(value);
    }

    template <class User>
    bool
    JsonReader::number(User& user, const JsonToken& token)
    {
        const char* memory = token.memory();

        if ( token.flag & Flag::Float )
            return number(user, (f32) strtod(memory, 0));

        if ( token.flag & Flag::Negat )
            return number(user, (i32) strtol(memory, 0, 10));

        return number(user, (u32) strtoul(memory, 0, 10));
    }

    template <class User>
    bool
    JsonReader::boolean(User& user, const JsonToken& token)
    {
        const char* memory = token.memory();

        if ( *memory == 't' )
            return user.boolean(true);

        return user.boolean(false);
    }

    template <class User>
    bool
    JsonReader::null(User& user, const JsonToken& token)
    {
        return user.null();
    }

    template <class User>
    bool
    JsonReader::object(User& user, u32 depth)
    {
        JsonToken token;
        u32       count = 0;

        if ( user.objectEnter(depth) == false )
            return false;

        for ( count = 0; true; count++ ) {
            token = m_lexer.next();

            if ( token.type == Type::ObjRPar )
                break;

            if ( token.type == Type::String ) {
                if ( user.objectEntry(token) == false )
                    return false;
            } else
                return false;

            token = m_lexer.next();

            if ( token.type == Type::Colon ) {
                token = m_lexer.next();

                if ( deduce(user, token, depth + 1) == false )
                    return false;
            } else
                return false;

            token = m_lexer.next();

            if ( token.type == Type::Comma ) continue;
            if ( token.type == Type::ObjRPar ) break;

            return false;
        }

        if ( user.objectLeave(depth, count) == false )
            return false;

        return true;
    }

    template <class User>
    bool
    JsonReader::array(User& user, u32 depth)
    {
        JsonToken token;
        u32       count = 0;

        if ( user.arrayEnter(depth) == false )
            return false;

        for ( count = 0; true; count++ ) {
            token = m_lexer.next();

            if ( token.type != Type::ArrRPar ) {
                if ( deduce(user, token, depth + 1) == false )
                    return false;
            } else
                break;

            token = m_lexer.next();

            if ( token.type == Type::Comma ) continue;
            if ( token.type == Type::ArrRPar ) break;

            return false;
        }

        if ( user.arrayLeave(depth, count) == false )
            return false;

        return true;
    }
} // namespace ma
