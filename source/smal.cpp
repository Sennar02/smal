#include <smal/Memory/import.hpp>
#include <time.h>

using namespace ma;

static u32  size       = 2048;
static char buff[2048] = {0};

int
main(int argc, const char* argv[])
{
    auto alloc = PoolAlloc {buff, size, 60};

    char* array[] = {
        alloc.acquire(),
        alloc.acquire(),
        alloc.acquire(),
        alloc.acquire(),
    };

    for ( u32 i = 0; i < 4; i++ )
        printf("%p\n", array[i]);

    srand(time(0));

    for ( u32 i = 0; i < 45; ) {
        u32 j = rand() % 4;

        if ( alloc.release(array[j]) )
            printf("\x1b[32m%u\x1b[0m ", j);
        else
            printf("\x1b[31m%u\x1b[0m ", j);

        if ( ++i % 15 == 0 )
            printf("\n");
    }

    return 0;
}
