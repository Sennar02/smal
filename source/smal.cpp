#include <smal/Memory/import.hpp>

#include <stdio.h> // printf

using namespace ma;

static const usize s_mem_len = g_MiB * 4;
static void*       s_mem_ptr = 0;

int
main(int argc, const char* argv[])
{
    s_mem_ptr = calloc(1, s_mem_len);

    Bucket<int> bucket = {s_mem_ptr, s_mem_len};
    Handle<int> handle = bucket.acquire();

    if ( bucket.release(handle) )
        printf("Released handle.\n");

    PageAlloc       alloc = {s_mem_ptr, s_mem_len, sizeof(int) * 16};
    PagedBlock<int> block = {alloc, 32};

    for ( usize i = 0; i < block.size(); ) {
        printf("%u ", block[i]);

        if ( ++i % 16 == 0 )
            printf("\n");
    }

    if ( block.resize(64) ) {
        printf("\n");

        for ( usize i = 0; i < block.size(); ) {
            printf("%u ", block[i]);

            if ( ++i % 16 == 0 )
                printf("\n");
        }
    }

    if ( block.resize(15) ) {
        printf("\n");

        for ( usize i = 0; i < block.size(); ) {
            printf("%u ", block[i]);

            if ( ++i % 16 == 0 )
                printf("\n");
        }
    }

    return 0;
}
