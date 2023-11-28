#include <smal/Struct/import.hpp>

#include <stdio.h> // printf

using namespace ma;

int
main(int argc, const char* argv[])
{
    Origin     origin = {g_MiB * 4};
    StackAlloc alloc  = {origin.memory(), origin.size()};

    ProxyAlloc<PoolAlloc> proxy = {alloc, g_KiB};

    ArrayList<int, PagedBlock> list = {proxy, 100};

    printf("%lu\n", list.size());

    return 0;
}
