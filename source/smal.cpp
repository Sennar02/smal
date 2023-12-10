#include <smal/Json/import.hpp>
#include <stdio.h>

using namespace ma;

static MemoryService g_memory =
    {g_MiB * 64};

static auto g_main = g_memory.create<PoolAlloc>(g_MiB * 32, g_KiB * 2);
static auto g_back = g_memory.create<StackAlloc>(g_MiB * 32);

int
main(int argc, const char* argv[])
{
    printf("%u, %u\n", g_main.size(), g_back.size());

    return 0;
}
