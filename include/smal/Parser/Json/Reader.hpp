#ifndef SMAL_PARSER_JSON_READER_HPP
#define SMAL_PARSER_JSON_READER_HPP

#include <smal/Parser/Json/Lexer.hpp>

namespace smal::Json
{
    class Reader
    {
    public:
        template <class Client>
        static bool
        read(Client& client, String& string);

        template <class Client>
        static bool
        string(Client& client, const Lexeme& lexeme);

        template <class Client>
        static bool
        number(Client& client, const Lexeme& lexeme);

        template <class Client>
        static bool
        boolean(Client& client, const Lexeme& lexeme);

        template <class Client>
        static bool
        null(Client& client);

        template <class Client>
        static bool
        object(Client& client, String& string);

        template <class Client>
        static bool
        array(Client& client, String& string);
    };
} // namespace smal::Json

#include <smal/Parser/impl/Json/Reader.tpp>

#endif // SMAL_PARSER_JSON_READER_HPP
