#ifndef BITE_PARSER_JSON_LEXER_HPP
#define BITE_PARSER_JSON_LEXER_HPP

#include <smal/Parser/Json/Piece.hpp>

namespace smal::Json
{
    class Lexer
    {
    public:
        /**
         *
         * @param string
         */
        Lexer(const String& string);

        /**
         *
         *
         * @return
         */
        Piece
        next();

    private:
        /**
         *
         *
         * @return
         */
        Piece
        number();

        /**
         *
         *
         * @return
         */
        Piece
        string();

        /**
         *
         * @param string
         * @param type
         *
         * @return
         */
        Piece
        symbol(const String& string, PieceType type);

    private:
        /**
         *
         */
        const char* m_string;

        /**
         *
         */
        usize m_length;
    };
} // namespace smal::Json

#endif // BITE_PARSER_JSON_LEXER_HPP
