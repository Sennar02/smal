#include <smal/Parser/Json/Lexer.hpp>

namespace ma::Json
{
    static String g_number = {"+-.eE0123456789", 15};
    static String g_float  = {".eE", 3};
    static String g_negat  = {"-", 1};
    static String g_string = {"\0\"\'", 3};

    static String g_true      = {"true", 4};
    static String g_false     = {"false", 5};
    static String g_null      = {"null", 4};
    static String g_obj_start = {"{", 1};
    static String g_obj_stop  = {"}", 1};
    static String g_arr_start = {"[", 1};
    static String g_arr_stop  = {"]", 1};
    static String g_colon     = {":", 1};
    static String g_comma     = {",", 1};
    static String g_finish    = {"\0", 1};

    Lexeme
    Lexer::next(String& string)
    {
        static String table = {"\40\t\n\r", 4};

        usize       length = string.length();
        const char* memory = string.memory();

        if ( memory != 0 && length != 0 ) {
            while ( true ) {
                if ( table.contains(*memory) )
                    memory += 1, length -= 1;
                else
                    break;
            }

            string = {memory, length};

            return match(string);
        }

        return {};
    }

    Lexeme
    Lexer::match(String& string)
    {
        switch ( *string.memory() ) {
            case '\"':
                return Lexer::string(string, '\"');

            case '\'':
                return Lexer::string(string, '\'');

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
                return Lexer::number(string);

            case 't':
                return Lexer::symbol(string, g_true, LexType::Boolean);

            case 'f':
                return Lexer::symbol(string, g_false, LexType::Boolean);

            case 'n':
                return Lexer::symbol(string, g_null, LexType::Null);

            case '{':
                return Lexer::symbol(string, g_obj_start, LexType::ObjOpen);

            case '}':
                return Lexer::symbol(string, g_obj_stop, LexType::ObjClose);

            case '[':
                return Lexer::symbol(string, g_arr_start, LexType::ArrOpen);

            case ']':
                return Lexer::symbol(string, g_arr_stop, LexType::ArrClose);

            case ':':
                return Lexer::symbol(string, g_colon, LexType::Colon);

            case ',':
                return Lexer::symbol(string, g_comma, LexType::Comma);

            case '\0':
                return Lexer::symbol(string, g_finish, LexType::Finish);

            default:
                break;
        }

        return {};
    }

    Lexeme
    Lexer::string(String& string, char separ)
    {
        const char* memory = string.memory();
        usize       length = string.length();
        const char* cursor = memory;
        String      result;

        if ( *cursor == separ )
            cursor += 1, length -= 1;
        else
            return {};

        while ( length != 0 ) {
            if ( g_string.contains(*cursor) == false )
                cursor += 1, length -= 1;
            else
                break;
        }

        if ( *cursor == separ )
            cursor += 1, length -= 1;
        else
            return {};

        result = {memory + 1, (usize) (cursor - memory) - 2};
        string = {cursor, length};

        return {result, LexType::String};
    }

    Lexeme
    Lexer::number(String& string)
    {
        const char* memory = string.memory();
        usize       length = string.length();
        const char* cursor = memory;
        u32         flag   = 0;
        String      result;

        while ( length != 0 ) {
            flag |= g_float.contains(*cursor) ? LexFlag::Floating : 0;
            flag |= g_negat.contains(*cursor) ? LexFlag::Negative : 0;

            if ( g_number.contains(*cursor) )
                cursor += 1, length -= 1;
            else
                break;
        }

        result = {memory, (usize) (cursor - memory)};
        string = {cursor, length};

        return {result, LexType::Number, flag};
    }

    Lexeme
    Lexer::symbol(String& string, const String& symbol, LexType type)
    {
        const char* memory = string.memory();
        usize       length = string.length();

        String result = {memory, symbol.length()};

        if ( symbol.equals(string) ) {
            memory += symbol.length();
            length -= symbol.length();

            string = {memory, length};

            return {result, type};
        }

        return {};
    }
} // namespace ma::Json
