#include <smal/Parser/Json/Reader.hpp>

namespace smal::Json
{
    template <class Handler>
    Reader<Handler>::Reader(const String& string)
        : m_lexer {string}
    { }

    template <class Handler>
    bool
    Reader<Handler>::read()
    {
        return this->value(this->m_lexer.next());
    }

    template <class Handler>
    bool
    Reader<Handler>::value(const Piece& piece)
    {
        switch ( piece.type() ) {
            case LexType::Floating:
                return this->floating(piece);
            case LexType::Relative:
                return this->relative(piece);
            case LexType::Absolute:
                return this->absolute(piece);
            case LexType::String:
                return this->string(piece);
            case LexType::Boolean:
                return this->boolean(piece);
            case LexType::Null:
                return this->null();
            case LexType::ObjOpen:
                return this->object();
            case LexType::ArrOpen:
                return this->array();

            default:
                return false;
        }

        return false;
    }

    template <class Handler>
    bool
    Reader<Handler>::floating(const Piece& piece)
    {
        f64   value = strtod(piece.memory(), 0);
        usize absol = (usize) value;
        isize relat = (isize) value;

        if ( value == absol )
            return Handler::absolute(value);
        if ( value == relat )
            return Handler::relative(value);

        return Handler::floating(value);
    }

    template <class Handler>
    bool
    Reader<Handler>::relative(const Piece& piece)
    {
        return Handler::relative(strtol(piece.memory(), 0, 10));
    }

    template <class Handler>
    bool
    Reader<Handler>::absolute(const Piece& piece)
    {
        return Handler::absolute(strtoul(piece.memory(), 0, 10));
    }

    template <class Handler>
    bool
    Reader<Handler>::string(const Piece& piece)
    {
        return Handler::string(piece.memory(), piece.length());
    }

    template <class Handler>
    bool
    Reader<Handler>::boolean(const Piece& piece)
    {
        if ( piece.memory()[0] == 't' )
            return Handler::boolean(true);

        return Handler::boolean(false);
    }

    template <class Handler>
    bool
    Reader<Handler>::null()
    {
        return Handler::null();
    }

    template <class Handler>
    bool
    Reader<Handler>::object()
    {
        Piece piece;
        usize count = 0;

        if ( Handler::objOpen() == false )
            return false;

        for ( ; true; count++ ) {
            piece = this->m_lexer.next();

            if ( piece.type() != LexType::String )
                return false;

            if ( Handler::objKey(piece.memory(), piece.length()) == false )
                return false;

            piece = this->m_lexer.next();

            if ( piece.type() != LexType::Colon )
                return false;

            piece = this->m_lexer.next();

            if ( piece.kind() != LexKind::Value )
                return false;

            if ( this->value(piece) == false )
                return false;

            piece = this->m_lexer.next();

            if ( piece.type() == LexType::Comma )
                continue;

            if ( piece.type() == LexType::ObjClose )
                break;

            return false;
        }

        return Handler::objClose(count + 1);
    }

    template <class Handler>
    bool
    Reader<Handler>::array()
    {
        Piece piece;
        usize count = 0;

        if ( Handler::arrOpen() == false )
            return false;

        for ( ; true; count++ ) {
            piece = this->m_lexer.next();

            if ( piece.kind() != LexKind::Value )
                return false;

            if ( this->value(piece) == false )
                return false;

            piece = this->m_lexer.next();

            if ( piece.type() == LexType::Comma )
                continue;

            if ( piece.type() == LexType::ArrClose )
                break;

            return false;
        }

        return Handler::arrClose(count + 1);
    }
} // namespace smal::Json
