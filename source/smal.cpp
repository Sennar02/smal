#include <smal/Memory/import.hpp>
#include <stdio.h> // printf

using namespace ma;

static const usize g_pool_size              = 2048;
static const usize g_pool_page              = 128;
static char*       g_pool_buff[g_pool_size] = {0};

int
main(int argc, const char* argv[])
{
    PoolAlloc pool = {
        g_pool_buff,
        g_pool_size,
        g_pool_page,
    };

    auto* piece = pool.acquire();

    if ( piece == 0 ) return 1;

    for ( usize i = 0; i < g_pool_page; i++ ) {
        printf("%2hhx ", piece[i]);

        if ( (i + 1) % 16 == 0 )
            printf("\n");
    }

    return 0;
}
