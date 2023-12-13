#include <smal/Memory/import.hpp>
#include <time.h>

using namespace ma;

int
main(int argc, const char* argv[])
{
    MemoryModule memory = {32, g_mib};
    ArenaAlloc   origin;

    memory.request(origin);

    printf("memory = %p, %u\n", origin.memory(), origin.size());

    printf("%i\n", origin.availab(sizeof(MemoryModule)));

    return 0;
}
