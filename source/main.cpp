#include <smal/Entity/import.hpp>
#include "game/App.hpp"

static const long memlen = 1024 * 1024 * 1024l;
static const long paglen = 1024 * 8l;

int
main(int argc, const char* argv[])
{
    char* memptr = (char*) calloc(1, memlen);

    {
        smal::PageAlloc  origin = {memptr + paglen, memlen - paglen, paglen};
        smal::ArenaAlloc buffer = {memptr, paglen};

        smal::Attributes attrib = {origin, buffer};

        App engine = {attrib};

        sf::RenderWindow window = {
            {1280, 720}, "App"
        };

        engine.loop(window);
    }

    free(memptr);

    return 0;
}
