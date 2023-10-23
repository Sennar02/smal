#ifndef SMAL_PARSER_JSON_LEXEME_HPP
#define SMAL_PARSER_JSON_LEXEME_HPP

#include <smal/Parser/String.hpp>

namespace smal::Json
{
    enum class LexType
    {
        // Literals
        String,
        Number,
        // Keywords
        Boolean,
        Null,
        // Separators
        ObjOpen,
        ObjClose,
        ArrOpen,
        ArrClose,
        Colon,
        Comma,
        // Auxiliaries
        Finish,
        Error,

        SIZE,
    };

    enum class LexKind
    {
        Literal,
        Keyword,
        Separator,
        Auxiliary,

        SIZE,
    };

    enum LexFlag
    {
        Floating = 1,
        Negative = 2,

        SIZE = 2,
    };

    class Lexeme
    {
    public:
        /**
         *
         *
         * @param string
         * @param type
         * @param flag
         */
        Lexeme(const String& string = {}, LexType type = LexType::Error, u32 flag = 0);

        /**
         *
         *
         * @return
         */
        LexType
        type() const;

        /**
         *
         *
         * @return
         */
        LexKind
        kind() const;

        /**
         *
         *
         * @return
         */
        usize
        length() const;

        /**
         *
         */
        u32
        flag() const;

        /**
         *
         *
         * @return
         */
        const char*
        memory() const;

    private:
        /**
         *
         */
        String m_string;

        /**
         *
         */
        LexType m_type;

        /**
         *
         */
        u32 m_flag;
    };
} // namespace smal::Json

#endif // SMAL_PARSER_JSON_LEXEME_HPP
