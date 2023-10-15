#include <smal/Memory/import.hpp>

static const usize g_zone = 1024 * 1024 * 8;
static const usize g_pool = 1024 * 1024 * 1016;
static const usize g_page = 1024 * 8;

int
main(int argc, const char* argv[])
{
    char* memory = (char*) calloc(1, g_zone + g_pool);

    {
        smal::PoolOrigin  pool = {memory, g_pool};
        smal::StackOrigin zone = {memory + g_pool, g_zone};

        smal::Creator<int> creator = {pool};

        for ( usize i = 0; i < 100; i++ ) {
            int* item = creator.create();

            if ( item != 0 )
                printf("%i\n", *item);
            else
                break;

            creator.destroy(item);
        }

        srand(time(0));
    }

    free(memory);

    return 0;
}
