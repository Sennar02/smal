#include <smal/Memory/import.hpp>

static const usize g_zone = 1024 * 1024 * 8;
static const usize g_pool = 1024 * 1024 * 1016;
static const usize g_page = 1024 * 8;

struct Position
{
    f32 x;
    f32 y;
};

int
main(int argc, const char* argv[])
{
    char* memory = (char*) calloc(1, g_zone + g_pool);

    {
        smal::PoolOrigin  pool = {memory, g_pool, g_page};
        smal::StackOrigin zone = {memory + g_pool, g_zone};

        smal::PagedArray<Position> array = {&pool};

        array.attach(1);

        for ( usize i = 0; i < array.length(); i++ ) {
            array[i] = {
                (f32) i,
                (f32) i,
            };

            printf("%.3f, %.3f\n",
                array[i].x,
                array[i].y);
        }
    }

    free(memory);

    return 0;
}
