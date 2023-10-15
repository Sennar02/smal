#include <smal/Struct/import.hpp>

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

        smal::ArrayList<Position> list = {&pool};

        list.insert({0.4, 11.5}, 0);

        bool b = list.contains({0.4, 11.5}, [](auto& a, auto& b) {
            return a.x == b.x &&
                   a.y == b.y;
        });

        printf("%i\n", b);
    }

    free(memory);

    return 0;
}
