#include <smal/Memory/import.hpp>

#include <stdio.h> // printf

using namespace ma;

int
main(int argc, const char* argv[])
{
    static Memory s_memory = {g_MiB * 4};
    static usize  s_size   = 64;

    auto  alloc = s_memory.create<PoolAlloc>(g_KiB * 2, s_size);
    auto* block = alloc.acquire();

    if ( block == 0 ) return 1;

    for ( usize i = 0; i < s_size; i++ ) {
        printf("%2hhx ", block[i]);

        if ( (i + 1) % 16 == 0 )
            printf("\n");
    }

    return 0;
}
