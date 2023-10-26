#ifndef BITE_PARSER_JSON_LEXER_HPP
#define BITE_PARSER_JSON_LEXER_HPP

#include <smal/Parser/Json/Lexeme.hpp>

namespace ma::Json
{
    class Lexer
    {
    public:
        /**
         *
         *
         * @return
         */
        static Lexeme
        next(String& string);

    private:
        /**
         *
         *
         * @param string
         *
         * @return
         */
        static Lexeme
        forward(String& string);

        /**
         *
         *
         * @return
         */
        static Lexeme
        string(String& string);

        /**
         *
         *
         * @return
         */
        static Lexeme
        number(String& string);

        /**
         *
         * @param string
         * @param symbol
         * @param type
         *
         * @return
         */
        static Lexeme
        symbol(String& string, const String& symbol, LexType type);
    };
} // namespace ma::Json

#endif // BITE_PARSER_JSON_LEXER_HPP
