#include <smal/Parser/import.hpp>
#include <string.h>

using namespace smal;

class Printer
{
public:
    bool
    string(const char* string, usize length)
    {
        for ( usize i = 0; i < length; i++ )
            printf("%c", string[i]);

        printf("\n");

        return true;
    }

    bool
    number(usize value)
    {
        printf("%lu\n", value);

        return true;
    }

    bool
    number(isize value)
    {
        printf("%li\n", value);

        return true;
    }

    bool
    number(f64 value)
    {
        printf("%lf\n", value);

        return true;
    }

    bool
    boolean(bool value)
    {
        static const char* values[] = {
            "false",
            "true",
        };

        printf("%s\n", values[(usize) value]);

        return true;
    }

    bool
    null()
    {
        printf("null\n");

        return true;
    }

    bool
    arrOpen()
    {
        return true;
    }

    bool
    arrClose(usize count)
    {
        return true;
    }

    bool
    objOpen()
    {
        return true;
    }

    bool
    objKey(const char* string, usize length)
    {
        printf("<");

        for ( usize i = 0; i < length; i++ )
            printf("%c", string[i]);

        printf(">\n");

        return true;
    }

    bool
    objClose(usize count)
    {
        return true;
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

    String  s = {buffer, strlen(buffer)};
    Reader  r;
    Printer p;

    if ( r.read(p, s) == false )
        return 1;

    return 0;
}
