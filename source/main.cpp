#include <smal/Parser/import.hpp>
#include <string.h>

int
main(int argc, const char* argv[])
{
    using namespace smal;
    using namespace smal::Json;

    char buffer[256] = {0};

    auto* file = fopen("../assets/prova.json", "r");

    fread(buffer, 256, 1, file);

    String s = {buffer, strlen(buffer)};
    Lexer  r = {s};

    while ( true ) {
        Piece p = r.next();

        if ( p.type() == PieceType::Finish ||
             p.length() == 0 )
            break;

        printf("%2lu:%lu ",
            (usize) p.type(),
            (usize) p.kind());

        for ( usize i = 0; i < p.length(); i++ )
            printf("%c", p.memory()[i]);

        printf("\n");
    }

    return 0;
}
