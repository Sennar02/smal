#ifndef SMAL_PARSER_JSON_PIECE_HPP
#define SMAL_PARSER_JSON_PIECE_HPP

#include <smal/Parser/String.hpp>

namespace smal::Json
{
    enum class PieceType
    {
        ObjOpen,
        ObjClose,
        ArrOpen,
        ArrClose,
        String,
        Floating,
        Signed,
        Unsigned,
        Boolean,
        Null,
        Colon,
        Comma,
        Comment,
        Finish,
        Error,
        SIZE,
    };

    enum class PieceKind
    {
        Value,
        Delim,
        Extra,
        SIZE,
    };

    class Piece
    {
    public:
        using Type = PieceType;
        using Kind = PieceKind;

        /**
         *
         *
         * @param string
         * @param type
         */
        Piece(const String& string = {}, PieceType type = Type::Error);

        /**
         *
         *
         * @return
         */
        PieceType
        type() const;

        /**
         *
         *
         * @return
         */
        PieceKind
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
        PieceType m_type;
    };
} // namespace smal::Json

#endif // SMAL_PARSER_JSON_PIECE_HPP
