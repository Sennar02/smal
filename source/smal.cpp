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
    Engine     e;
    TitleState t;

    if ( e.attach("Title", t) )
        return e.loop("Title", 120u) == false;

    return 1;
}
