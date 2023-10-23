#include <smal/Parser/Json/Reader.hpp>

namespace smal::Json
{
    template <class Client>
    bool
    Reader::read(Client& client, String& string)
    {
        auto lexeme = Lexer::next(string);

        if ( lexeme.length() != 0 ) {
            switch ( lexeme.type() ) {
                case LexType::String: return Reader::string(client, lexeme);
                case LexType::Number: return Reader::number(client, lexeme);
                case LexType::Boolean: return Reader::boolean(client, lexeme);
                case LexType::Null: return Reader::null(client);
                case LexType::ObjOpen: return Reader::object(client, string);
                case LexType::ArrOpen: return Reader::array(client, string);

                default:
                    break;
            }
        }

        return false;
    }

    template <class Client>
    bool
    Reader::string(Client& client, const Lexeme& lexeme)
    {
        const char* memory = lexeme.memory();
        usize       length = lexeme.length();

        return client.string(memory, length);
    }

    template <class Client>
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

    template <class Client>
    bool
    Reader::boolean(Client& client, const Lexeme& lexeme)
    {
        if ( *lexeme.memory() == 't' )
            return client.boolean(true);

        return client.boolean(false);
    }

    template <class Client>
    bool
    Reader::null(Client& client)
    {
        return client.null();
    }

    template <class Client>
    bool
    Reader::object(Client& client, String& string)
    {
        const char* memory = 0;
        usize       length = 0;
        usize       count  = 0;
        Lexeme      lexeme;

        if ( client.objOpen() == false ) return false;

        for ( ; true; count++ ) {
            lexeme = Lexer::next(string);
            memory = lexeme.memory();
            length = lexeme.length();

            if ( lexeme.type() != LexType::String )
                return false;

            if ( client.objKey(memory, length) == false )
                return false;

            lexeme = Lexer::next(string);

            if ( lexeme.type() != LexType::Colon )
                return false;

            if ( Reader::read(client, string) == false )
                return false;

            lexeme = Lexer::next(string);

            if ( lexeme.type() == LexType::Comma ) continue;
            if ( lexeme.type() == LexType::ObjClose ) break;

            return false;
        }

        return client.objClose(count + 1);
    }

    template <class Client>
    bool
    Reader::array(Client& client, String& string)
    {
        usize  count = 0;
        Lexeme lexeme;

        if ( client.arrOpen() == false ) return false;

        for ( ; true; count++ ) {
            if ( Reader::read(client, string) == false )
                return false;

            lexeme = Lexer::next(string);

            if ( lexeme.type() == LexType::Comma ) continue;
            if ( lexeme.type() == LexType::ArrClose ) break;

            return false;
        }

        return client.arrClose(count + 1);
    }
} // namespace smal::Json
