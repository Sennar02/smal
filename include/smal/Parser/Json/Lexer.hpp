#ifndef BITE_PARSER_JSON_LEXER_HPP
#define BITE_PARSER_JSON_LEXER_HPP

#include <smal/Parser/Json/Lexeme.hpp>

namespace smal::Json
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
        lexeme(String& string);

        /**
         *
         *
         * @return
         */
        static Lexeme
        number(String& string);

        /**
         *
         *
         * @return
         */
        static Lexeme
        string(String& string);

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
} // namespace smal::Json

#endif // BITE_PARSER_JSON_LEXER_HPP
