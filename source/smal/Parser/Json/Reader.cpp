#include <smal/Parser/Json/Reader.hpp>

namespace ma::Json
{
    bool
    Reader::read(Client& client, String& string)
    {
        return match(client, string, Lexer::next(string), 0);
    }

    bool
    Reader::match(Client& client, String& string, const Lexeme& lexeme, usize depth)
    {
        if ( lexeme.length() == 0 )
            return false;

        switch ( lexeme.type() ) {
            case LexType::String:
                return Reader::string(client, lexeme);

            case LexType::Number:
                return Reader::number(client, lexeme);

            case LexType::Boolean:
                return Reader::boolean(client, lexeme);

            case LexType::Null:
                return Reader::null(client);

            case LexType::ObjOpen:
                return Reader::object(client, string, depth + 1);

            case LexType::ArrOpen:
                return Reader::array(client, string, depth + 1);

            default:
                break;
        }

        return false;
    }

    bool
    Reader::string(Client& client, const Lexeme& lexeme)
    {
        const char* memory = lexeme.memory();
        usize       length = lexeme.length();

        return client.string(memory, length);
    }

    bool
    Reader::number(Client& client, const Lexeme& lexeme)
    {
        const char* memory = lexeme.memory();

        f64 num = 0;

        if ( (lexeme.flag() & LexFlag::Floating) != 0 ) {
            num = strtod(memory, 0);

            if ( num == (isize) num )
                return client.number((isize) num);
            if ( num == (usize) num )
                return client.number((usize) num);

            return client.number(num);
        }

        if ( (lexeme.flag() & LexFlag::Negative) != 0 )
            return client.number((isize) strtol(memory, 0, 10));

        return client.number((usize) strtoul(memory, 0, 10));
    }

    bool
    Reader::boolean(Client& client, const Lexeme& lexeme)
    {
        if ( *lexeme.memory() == 't' )
            return client.boolean(true);

        return client.boolean(false);
    }

    bool
    Reader::null(Client& client)
    {
        return client.null();
    }

    bool
    Reader::object(Client& client, String& string, usize depth)
    {
        const char* memory = 0;
        usize       length = 0;
        usize       count  = 0;
        Lexeme      lexeme;

        if ( client.object_start(depth) == false ) return false;

        for ( ; true; count++ ) {
            lexeme = Lexer::next(string);
            memory = lexeme.memory();
            length = lexeme.length();

            if ( lexeme.type() == LexType::ObjClose ) break;
            if ( lexeme.type() != LexType::String ) return false;

            if ( client.name(memory, length) == false )
                return false;

            lexeme = Lexer::next(string);

            if ( lexeme.type() != LexType::Colon ) return false;

            lexeme = Lexer::next(string);

            if ( match(client, string, lexeme, depth) == false )
                return false;

            lexeme = Lexer::next(string);

            if ( lexeme.type() == LexType::Comma ) continue;
            if ( lexeme.type() == LexType::ObjClose ) break;

            return false;
        }

        return client.object_stop(depth, count);
    }

    bool
    Reader::array(Client& client, String& string, usize depth)
    {
        usize  count = 0;
        Lexeme lexeme;

        if ( client.array_start(depth) == false ) return false;

        for ( ; true; count++ ) {
            lexeme = Lexer::next(string);

            if ( lexeme.type() == LexType::ArrClose ) break;

            if ( match(client, string, lexeme, depth) == false )
                return false;

            lexeme = Lexer::next(string);

            if ( lexeme.type() == LexType::Comma ) continue;
            if ( lexeme.type() == LexType::ArrClose ) break;

            return false;
        }

        return client.array_stop(depth, count);
    }
} // namespace ma::Json
