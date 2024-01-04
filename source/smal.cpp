#include <smal/Signal/import.hpp>
#include <time.h>

using namespace ma;

int
main(int argc, const char* argv[])
{
    PoolOrigin origin =
        g_memory.request<PoolOrigin>(g_mib * 8u, g_kib * 1u);

    HashTable<u32, const char*, PagedBuffer> table = {
        origin,
        64u,
        origin.page(),
    };

    table.insert(256u, "A");
    table.insert(257u, "B");
    table.insert(258u, "C");

    printf("table_size = %u\n", table.size());

    table.forEach([](auto& x, auto& y) {
        printf("%u -> %s\n", x, y);
    });

    printf("\n");

    if ( table.resize(512u) ) {
        printf("table_size = %u\n", table.size());

        table.insert(255u, "D");

        printf("%u -> %s\n", 255u, table[255u]);
        printf("%u -> %s\n", 256u, table[256u]);
        printf("%u -> %s\n", 257u, table[257u]);
        printf("%u -> %s\n", 258u, table[258u]);
    } else
        printf("<error>\n");

    return 0;
}
