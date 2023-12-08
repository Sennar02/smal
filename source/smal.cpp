#include <smal/Json/import.hpp>
#include <stdio.h>

using namespace ma;

static MemoryService g_memory =
    {g_MiB * 64};

static auto g_main = g_memory.create<PoolAlloc>(g_MiB * 20, g_KiB * 2);
static auto g_back = g_memory.create<StackAlloc>(g_MiB * 20);

int
main(int argc, const char* argv[])
{
    String a = "ciao";
    String b;

    printf("[%s], [%s]\n",
        a.memory(),
        b.memory());

    b = a;

    printf("[%s], [%s]\n",
        a.memory(),
        b.memory());

    return 0;
}
