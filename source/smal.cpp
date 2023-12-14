#include <smal/Memory/import.hpp>
#include <time.h>

using namespace ma;

static const u32 size       = 2048;
static char      buff[size] = {0};

int
main(int argc, const char* argv[])
{
    ArenaOrigin origin = {buff, size};

    auto buffer =
        SimpleBuffer<int>(origin, 20);

    printf("%u\n", buffer.size());

    for ( u32 i = 0; i < buffer.size(); i++ )
        printf("%u ", buffer[i] = 1);
    printf("\n");

    origin.prepare();

    for ( u32 i = 0; i < buffer.size(); i++ )
        printf("%u ", buffer[i]);
    printf("\n");

    return 0;
}
