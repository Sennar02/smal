#include <smal/Struct/import.hpp>
#include <stdio.h>

static const long g_length = 64 * 6;
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

    for ( long i = 0; i < vector.get_length(); i++ ) {
        if ( i % 16 == 0 )
            printf("  ");

        printf("%02i, ", vector[i] = (i + 100));

        if ( (i + 1) % 16 == 0 )
            printf("\n");
    }

    vector.expand(2);

    printf("]\n\nVector ( %3li ): [\n", vector.get_length());

    for ( long i = 0; i < vector.get_length(); i++ ) {
        if ( i % 16 == 0 )
            printf("  ");

        printf("%02i, ", vector[i] = (i + 100));

        if ( (i + 1) % 16 == 0 )
            printf("\n");
    }

    vector.shrink(1);

    printf("]\n\nVector ( %3li ): [\n", vector.get_length());

    for ( long i = 0; i < vector.get_length(); i++ ) {
        if ( i % 16 == 0 )
            printf("  ");

        printf("%02i, ", vector[i]);

        if ( (i + 1) % 16 == 0 )
            printf("\n");
    }

    printf("]\n\n");

    for ( long i = 0; i < origin.get_length(); ) {
        printf("%2hhx ", g_memory[i]);

        i += 1;

        if ( i % 4 == 0 )
            printf("\t");
        if ( i % 16 == 0 )
            printf("\n");
    }

    free(g_memory);

    return 0;
}
