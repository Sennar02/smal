#include <smal/Parser/Json/Lexer.hpp>

namespace smal::Json
{

    static String g_number = {"+-.eE0123456789", 15};
    static String g_float  = {".eE", 3};
    static String g_negat  = {"-", 1};
    static String g_string = {"\0\"", 2};

    Lexer::Lexer(const String& string)
        : m_string {string.memory()}
        , m_length {string.length()}
    { }

    Piece
    Lexer::next()
    {
        static String table = {"\40\t\n\r", 4};

        char byte = 0;

        if ( this->m_length != 0 && this->m_string != 0 ) {
            while ( true ) {
                byte = *this->m_string;

                if ( table.contains(byte) )
                    this->m_string += 1;
                else
                    break;
            }

            switch ( byte ) {
                case '-':
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    return this->number();
                case '"':
                    return this->string();
                case 't':
                    return this->symbol({"true", 4}, PieceType::Boolean);
                case 'f':
                    return this->symbol({"false", 5}, PieceType::Boolean);
                case 'n':
                    return this->symbol({"null", 4}, PieceType::Boolean);
                case '{':
                    return this->symbol({"{", 1}, PieceType::ObjOpen);
                case '}':
                    return this->symbol({"}", 1}, PieceType::ObjClose);
                case '[':
                    return this->symbol({"[", 1}, PieceType::ArrOpen);
                case ']':
                    return this->symbol({"]", 1}, PieceType::ArrClose);
                case ':':
                    return this->symbol({":", 1}, PieceType::Colon);
                case ',':
                    return this->symbol({",", 1}, PieceType::Comma);
                case '\0':
                    return this->symbol({"\0", 1}, PieceType::Finish);
                case '/':
                    return {}; // this->comment();
            }
        }

        return {};
    }

    Piece
    Lexer::number()
    {
        usize       length = 0;
        const char* cursor = this->m_string;
        char        byte   = 0;
        char        flag   = 0;
        String      result;

        while ( true ) {
            byte = *cursor;

            if ( g_float.contains(byte) ) flag |= 2;
            if ( g_negat.contains(byte) ) flag |= 1;

            if ( g_number.contains(byte) )
                cursor += 1;
            else
                break;
        }

        length = cursor - this->m_string;
        result = {this->m_string, length};

        if ( length <= this->m_length ) {
            this->m_string += length;
            this->m_length -= length;

            if ( (flag & 2) != 0 ) return {result, PieceType::Floating};
            if ( (flag & 1) != 0 ) return {result, PieceType::Signed};

            return {result, PieceType::Unsigned};
        }

        return {};
    }

    Piece
    Lexer::string()
    {
        usize       length = 0;
        const char* cursor = this->m_string;
        char        byte   = 0;
        String      result;

        if ( *cursor++ != '\"' )
            return {};

        while ( true ) {
            byte = *cursor;

            if ( g_string.contains(byte) == false )
                cursor += 1;
            else
                break;
        }

        if ( *cursor++ != '\"' )
            return {};

        length = cursor - this->m_string - 2;
        result = {this->m_string + 1, length};

        if ( length <= this->m_length ) {
            this->m_string += length + 2;
            this->m_length -= length + 2;

            return {result, PieceType::String};
        }

        return {};
    }

    Piece
    Lexer::symbol(const String& string, PieceType type)
    {
        usize  length = string.length();
        String result = {this->m_string, length};

        if ( string.equals(result) ) {
            this->m_string += length;
            this->m_length -= length;

            return {result, type};
        }

        return {};
    }
} // namespace smal::Json
