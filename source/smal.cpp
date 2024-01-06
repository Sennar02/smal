#include <smal/Engine/import.hpp>

using namespace ma;

int
main(int argc, const char* argv[])
{
    Engine game;

    if ( game.isActive() )
        game.loop(0);

    return 0;
}
