#include <smal/Algo/import.hpp>

#include <stdio.h>

using namespace ma;

static auto g_memory =
    MemoryService {g_MiB * 64};

int
main(int argc, const char* argv[])
{
    PoolAlloc alloc = g_memory.create<PoolAlloc>(g_MiB * 63, g_KiB);

    HashTable<String, String, PagedBlock> table =
        {alloc, 10};

    for ( i32 i = 1; i < argc; i++ )
        table.insert(argv[1], "");

    HashTableForwIter iter = {table};

    if ( table.count() == 0 )
        return 0;

    table.forEach(iter, [](const String& name, const String& item) {
        printf("%s -> %s\n", name.memory(), item.memory());
    });

    return 0;
}
