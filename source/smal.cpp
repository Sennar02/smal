#include <smal/Memory/import.hpp>
#include <time.h>

using namespace ma;

int
main(int argc, const char* argv[])
{
    MemoryModule memory;
    PoolOrigin   origin;

    memory.request(origin, 2056u, 128u);

    PagedBuffer<int> buffer = {origin, 16u};

    if ( buffer.size() >= 16u )
        printf("%u\n", buffer.resize(0));

    return 0;
}
