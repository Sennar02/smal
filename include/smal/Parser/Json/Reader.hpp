#ifndef SMAL_PARSER_JSON_READER_HPP
#define SMAL_PARSER_JSON_READER_HPP

#include <smal/Parser/Json/Lexer.hpp>

namespace smal::Json
{
    template <class Handler>
    class Reader
    {
    public:
        Reader(const String& string);

        bool
        read();

    private:
        bool
        value(const Piece& piece);

        bool
        floating(const Piece& piece);

        bool
        relative(const Piece& piece);

        bool
        absolute(const Piece& piece);

        bool
        string(const Piece& piece);

        bool
        null();

        bool
        boolean(const Piece& piece);

        bool
        object();

        bool
        array();

    private:
        Lexer m_lexer;
    };
} // namespace smal::Json

#include <smal/Parser/impl/Json/Reader.tpp>

#endif // SMAL_PARSER_JSON_READER_HPP
