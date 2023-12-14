#include <smal/Memory/import.hpp>
#include <time.h>

using namespace ma;

static const u32 size       = 2048;
static char      buff[size] = {0};

int
main(int argc, const char* argv[])
{
    PoolOrigin origin {buff, size, 128};

    char* memory = origin.acquire();

    printf("%p\n", memory);
    printf("%i\n", origin.release(memory));
    printf("%i\n", origin.release(memory + 1));
    printf("%i\n", origin.release(memory));

    return 0;
}
