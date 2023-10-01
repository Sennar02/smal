#include <smal/Struct/import.hpp>
#include <stdio.h>

static const long g_length = 1024 * 1024 * 1024l;
static const long g_page   = 1024 * 4l;
static char*      g_memory = 0;

int
main(int argc, const char* argv[])
{
    g_memory = (char*) calloc(1, g_length);

    smal::PageTable table  = {g_memory, 2 * g_page, g_page};
    smal::PageAlloc origin = {g_memory + 2 * g_page, g_length - 2 * g_page, g_page};

    smal::Vector<int> vector = {origin, table};

    vector.resize(1'000'000);

    printf("%li\n", vector.length());

    for ( long i = 0; i < vector.length(); i++ )
        vector[i] = i;

    free(g_memory);

    return 0;
}
