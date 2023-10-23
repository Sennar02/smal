#include <smal/Parser/import.hpp>
#include <string.h>

using namespace smal;

class Printer
{
public:
    static bool
    objOpen()
    {
        return true;
    }

    static bool
    objKey(const char* string, usize length)
    {
        if ( strncmp("tilemap", string, length) == 0 )
            return true;

        return false;
    }

    static bool
    objClose(usize count)
    {
        if ( count == 1 )
            return true;

        return false;
    }

    static bool
    arrOpen()
    {
        return true;
    }

    static bool
    arrClose(usize count)
    {
        return true;
    }

    static bool
    absolute(usize value)
    {
        printf("%lu\n", value);

        return true;
    }

    static bool
    floating(f64 value)
    {
        return false;
    }

    static bool
    relative(isize value)
    {
        return false;
    }

    static bool
    string(const char* string, usize length)
    {
        return false;
    }

    static bool
    boolean(bool value)
    {
        return false;
    }

    static bool
    null()
    {
        return false;
    }
};

int
main(int argc, const char* argv[])
{
    using namespace smal;
    using namespace smal::Json;

    char buffer[256] = {0};

    auto* file = fopen("../assets/prova.json", "r");

    fread(buffer, 256, 1, file);

    String s = {buffer, strlen(buffer)};
    Lexeme l;

    while ( true ) {
        l = Lexer::lexeme(s);

        if ( l.type() == LexType::Finish )
            break;

        if ( l.type() == LexType::Error )
            return 1;

        printf("(%lu:%lu:%u) -> [%lu '",
            (usize) l.type(),
            (usize) l.kind(),
            l.flag(),
            l.length());

        for ( usize i = 0; i < l.length(); i++ ) {
            if ( l.memory()[i] != '\n' )
                printf("%c", l.memory()[i]);
        }

        printf("']\n");
    }

    return 0;
}
