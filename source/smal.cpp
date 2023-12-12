#include <smal/Memory/import.hpp>
#include <stdio.h>

using namespace ma;

static u32  size       = 2048;
static char buff[2048] = {0};

int
main(int argc, const char* argv[])
{
    auto  alloc = PoolAlloc {buff, size, 64};
    char* piece = alloc.acquire();

    printf("%i\n", alloc.release(piece));
    printf("%i\n", alloc.release(piece));

    return 0;
}
