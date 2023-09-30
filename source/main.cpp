#include <smal/Struct/import.hpp>
#include <stdio.h>

static const long g_length = 1024 * 1024l;
static char*      g_memory = 0;

int
main(int argc, const char* argv[])
{
    g_memory = (char*) calloc(1, g_length);

    smal::PageAlloc origin = {g_memory, g_length, 4 * 1024l};

    smal::Page      space = origin.reserve();
    smal::PageTable table = {
        space.memory(),
        space.length(),
        space.length(),
    };

    smal::Vector<int> vector = {origin, table};

    for ( long i = 0; i < 512l; i++ ) {
        if ( vector.isFull() )
            vector.resize(smal::Math::max(vector.length() * 1.5, 32.0));

        if ( vector.insert(i) == false )
            break;
    }

    printf("Vector:\n");

    for ( long i = 0; i < vector.size(); ) {
        printf("%3i ", vector[i]);

        if ( ++i % 32 == 0 )
            printf("\n");
    }

    printf("\nVector size: %li\n",
        vector.length());

    free(g_memory);

    return 0;
}
