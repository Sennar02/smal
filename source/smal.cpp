#include "TitleState.hpp"
#include "PauseState.hpp"

using namespace ma;

int
main(int argc, const char* argv[])
{
    Engine     game;
    TitleState title;
    PauseState pause;

    printf("attach state = %u\n", game.attach<TitleState>(title));
    printf("attach state = %u\n", game.attach<PauseState>(pause));

    if ( game.isActive() )
        printf("loop = %u\n", game.loop(StateTag::get<TitleState>()));

    return 0;
}
