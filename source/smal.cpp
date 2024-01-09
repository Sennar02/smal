#include <smal/Engine/import.hpp>

using namespace ma;

class TitleState
    : public State
{
public:
    TitleState()
        : State()
    { }
};

int
main(int argc, const char* argv[])
{
    Engine     game;
    TitleState title;

    game.attach("Title", title);

    printf("loop = %u\n", game.loop("Title"));

    return 0;
}
