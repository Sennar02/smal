#include <smal/Struct/import.hpp>
#include <stdio.h>

using namespace ma;

template <class List>
void
print(int& x, u32 i, const List& l)
{
    printf("%u | %i\n", i, x);

    if ( i + 1 == l.count() )
        printf("\n");
}

int
main(int argc, const char* argv[])
{
    Origin     mem   = {g_MiB * 4};
    StackAlloc alloc = {mem.memory(), mem.size()};

    ArrayList<int, PagedBlock> array = {
        PoolAlloc {mem.memory(), mem.size(), g_KiB}, 100, 5
    };

    array.insert(10, g_max_i32);

    array.for_each(
        action<print<ArrayList<int, PagedBlock>>>());

    Action func = {[](const int& a, const int& b) {
        return a >= b;
    }};

    array.remove(g_min_i32);

    array.for_each(Action {
        bind<print<ArrayList<int, PagedBlock>>>,
    });

    if ( array.contains(0, func) )
        printf("Array contains x >= 0\n");

    array.clear(Action {[](int x, u32 i) {
        destroy(x);
    }});

    return 0;
}
