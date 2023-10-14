#include <smal/Entity/import.hpp>
#include "game/App.hpp"

static const usize memlen = 1024ul * 1024 * 1024;
static const usize paglen = 1024ul * 128;

int
main(int argc, const char* argv[])
{
    char* memptr = (char*) calloc(1, memlen);

    {
        smal::PageAlloc  origin = {memptr + paglen, memlen - paglen, paglen};
        smal::ArenaAlloc buffer = {memptr, paglen};
        smal::Attributes holder = {origin, buffer};

        App engine = {holder};

        // clang-format off
        sf::RenderWindow window = {{1280, 720}, "App"};
        // clang-format on

        engine.loop(window);
    }

    free(memptr);

    return 0;
}
