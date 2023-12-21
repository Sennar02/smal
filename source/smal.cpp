#include <smal/Memory/import.hpp>
#include <time.h>

using namespace ma;

int
main(int argc, const char* argv[])
{
    MemoryModule     memory;
    StackOrigin      origin;
    PagedBuffer<int> buffer;

    memory.request(origin, 16u * 1024u);

    buffer = {origin, 16u, 256u};

    if ( buffer.size() != 0 )
        printf("%u\n", buffer.size());
    else
        printf("<error>\n");

    printf("%u\n", buffer.resize(0));

    return 0;
}
