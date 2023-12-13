#include <smal/Memory/import.hpp>
#include <time.h>

using namespace ma;

static const u32 size       = 250;
static char      buff[size] = {0};

int
main(int argc, const char* argv[])
{
    auto alloc = SplitAlloc {buff, size, 32};

    for ( u32 i = 1; i < 10; i++ ) {
        u32   size1 = i * 10;
        u32   size2 = i * 30;
        u32   size3 = i * 50;
        char* pntr1 = 0;
        char* pntr2 = 0;
        char* pntr3 = 0;

        printf("request: %3u\n", size1);

        pntr1 = alloc.acquire(size1);

        printf("acquire: %p, %3u\n", pntr1, size1);
        printf("request: %3u\n", size2);

        pntr2 = alloc.acquire(size2);

        printf("acquire: %p, %3u\n", pntr2, size2);
        printf("request: %3u\n", size3);

        pntr3 = alloc.acquire(size3);

        printf("acquire: %p, %3u\n", pntr3, size3);
        printf("request: %p, %3u\n", pntr1, size1);
        printf("release: %i\n", alloc.release(pntr1));
        printf("request: %p, %3u\n", pntr2, size2);
        printf("release: %i\n", alloc.release(pntr2));
        printf("request: %p, %3u\n", pntr3, size3);
        printf("release: %i\n", alloc.release(pntr3));
    }

    return 0;
}
