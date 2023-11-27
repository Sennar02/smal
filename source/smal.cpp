#include <smal/Memory/import.hpp>

#include <stdio.h> // printf

using namespace ma;

int
main(int argc, const char* argv[])
{
    Origin origin = {g_MiB * 4};

    Bucket<int> bucket = {origin.memory(), origin.size()};
    Handle<int> handle = bucket.acquire();

    if ( bucket.release(handle) )
        printf("Released handle.\n");

    StackAlloc      alloc = {origin.memory(), origin.size()};
    PagedBlock<int> block = {alloc, 0, 128};

    printf("avail = %lu\n", alloc.avail());

    block.resize(256);

    printf("avail = %lu\n", alloc.avail());

    for ( usize i = 0; i < block.size(); ) {
        printf("%u ", block[i]);

        if ( ++i % 16 == 0 )
            printf("\n");
    }

    block.resize(0);

    printf("avail = %lu\n", alloc.avail());

    return 0;
}
