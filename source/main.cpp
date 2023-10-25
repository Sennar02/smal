#include <smal/Memory/import.hpp>
#include <smal/Parser/import.hpp>

#include <string.h>

class Client
    : public ma::Json::Client
{ };

static const ma::usize g_pool = 1024 * 1024 * 16;
static const ma::usize g_parr = 1024 * 1024 * 12;
static const ma::usize g_page = 1024 * 32;

static char g_buff[g_page] = {0};

int
main(int argc, const char* argv[])
{
    using namespace ma;

    auto* file = fopen("../assets/doc.json", "r");
    usize size = 0;
    usize prev = 0;

    if ( file == 0 )
        return 1;

    char* memory = (char*) calloc(1, g_pool);

    {
        StackOrigin      pool = {memory, g_pool};
        FixedArray<char> parr = {&pool, g_parr};

        while ( true ) {
            size = fread(g_buff, 1, g_page - 1, file);

            g_buff[size] = 0;

            for ( usize i = 0; i < size; i++ )
                parr[prev + i] = g_buff[i];

            prev += size;

            if ( size != g_page - 1 )
                break;
        }

        fclose(file);

        Client c;
        String s = {&parr[0], prev};

        // clang-format off
        printf("Read \x1b[34m%.6f\x1b[0m MB from \x1b[34m'%s'\x1b[0m\n",
            prev / (1000000.f), "../assets/doc.json");
        // clang-format on

        if ( Json::Reader::read(c, s) == false )
            printf("-> \x1b[31mFailure\x1b[0m\n");
        else
            printf("-> \x1b[32mSuccess\x1b[0m\n");
    }

    free(memory);

    return 0;
}
