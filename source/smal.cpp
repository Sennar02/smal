#include <smal/Memory/import.hpp>
#include <time.h>

using namespace ma;

int
main(int argc, const char* argv[])
{
    MemoryModule memory;
    SplitOrigin  origin;

    memory.request(origin, 1024, 32u);

    char* blocks[] = {
        origin.acquire(20),
        origin.acquire(40),
        origin.acquire(60),
        origin.acquire(80),
        origin.acquire(100),
    };

    for ( u32 i = 0; i < 5; i++ )
        origin.release(blocks[i]);

    return 0;
}
