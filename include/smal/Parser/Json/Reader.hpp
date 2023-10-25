#ifndef SMAL_PARSER_JSON_READER_HPP
#define SMAL_PARSER_JSON_READER_HPP

#include <smal/Parser/Json/Lexer.hpp>
#include <smal/Parser/Json/Client.hpp>

namespace ma::Json
{
    class Reader
    {
    public:
        /**
         *
         *
         * @param client
         * @param string
         *
         * @return True.
         * @return False.
         */
        static bool
        read(Client& client, String& string);

    private:
        /**
         *
         *
         * @param client
         * @param string
         * @param lexeme
         * @param depth
         *
         * @return True.
         * @return False.
         */
        static bool
        forward(Client& client, String& string, const Lexeme& lexeme, usize depth);

        /**
         *
         *
         * @param client
         * @param lexeme
         *
         * @return True.
         * @return False.
         */
        static bool
        string(Client& client, const Lexeme& lexeme);

        /**
         *
         *
         * @param client
         * @param lexeme
         *
         * @return True.
         * @return False.
         */
        static bool
        number(Client& client, const Lexeme& lexeme);

        /**
         *
         *
         * @param client
         * @param lexeme
         *
         * @return True.
         * @return False.
         */
        static bool
        boolean(Client& client, const Lexeme& lexeme);

        /**
         *
         *
         * @param client
         *
         * @return True.
         * @return False.
         */
        static bool
        null(Client& client);

        /**
         *
         *
         * @param client
         * @param string
         * @param depth
         *
         * @return True.
         * @return False.
         */
        static bool
        object(Client& client, String& string, usize depth);

        /**
         *
         *
         * @param client
         * @param string
         * @param depth
         *
         * @return True.
         * @return False.
         */
        static bool
        array(Client& client, String& string, usize depth);
    };
} // namespace ma::Json

#endif // SMAL_PARSER_JSON_READER_HPP
