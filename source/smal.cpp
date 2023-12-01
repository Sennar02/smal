#include <smal/Struct/import.hpp>

#include <stdio.h> // printf

using namespace ma;

static auto g_memory =
    MemoryService {g_MiB * 64};

void
print(int& x, u32 i, const ArrayList<int, PagedBlock>& l)
{
    if ( i == 0 )
        printf("[\n");

    printf("  %2u: %i\n", i, x);

    if ( i + 1 == l.count() )
        printf("]\n");
}

int
main(int argc, const char* argv[])
{
    ChainAlloc chain = {
        g_memory.create<PoolAlloc>(g_MiB * 4, 8u),
        g_memory.create<PoolAlloc>(g_MiB * 8, 16u),
        g_memory.create<StackAlloc>(g_MiB * 4),
    };

    auto& stack = chain.alloc<2>();
    auto  avail = stack.avail();

    auto pool = PoolAlloc {stack.acquire(avail), avail, g_KiB};

    ArrayList<int, PagedBlock> array = {pool, 10, 5};

    printf("size = %u / %u\n",
        array.count(),
        array.size());

    printf("insert(%i, %li) = %i\n",
        10,
        g_max_i32,
        array.insert(10, g_max_i32));

    array.for_each(action<print>());

    Action func = {[](const int& a, const int& b) {
        return a >= b;
    }};

    printf("remove(%li) = %i\n",
        g_max_i32,
        array.remove(g_min_i32));

    array.for_each(Action {
        bind<print>,
    });

    if ( array.contains(10, func) )
        printf("array has item >= 10\n");

    array.clear(
        action([](int& x) {
            printf("%i\n", x);
        }));

    return 0;
}
