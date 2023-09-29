#include <smal/Struct/import.hpp>
#include <stdio.h>

static const long g_length = 8 * 1024 * 1024;
static char*      g_memory = 0;

int
main(int argc, const char* argv[])
{
    g_memory = (char*) calloc(1, g_length);

    smal::PageAlloc origin = {g_memory, g_length, 64};

    smal::Page      space = origin.reserve();
    smal::PageTable table = {
        space.get_memory(),
        space.get_length(),
        space.get_length(),
    };

    smal::Vector<int> vector = {origin, table};

    printf("Vector ( %3li ): [\n", vector.get_length());

    for ( long i = 0; i < vector.get_length(); i++ )
        printf("  %i\n", vector[i] = i);

    vector.expand(2);

    printf("]\nVector ( %3li ): [\n", vector.get_length());

    for ( long i = 0; i < vector.get_length(); i++ )
        printf("  %i\n", vector[i] = i);

    vector.shrink(1);

    printf("]\nVector ( %3li ): [\n", vector.get_length());

    for ( long i = 0; i < vector.get_length(); i++ )
        printf("  %i\n", vector[i]);

    printf("]\n");

    free(g_memory);

    return 0;
}
