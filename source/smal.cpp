#include <smal/Struct/import.hpp>
#include <stdio.h>

using namespace ma;

int
main(int argc, const char* argv[])
{
    Origin     mem   = {g_MiB * 4};
    StackAlloc alloc = {mem.memory(), mem.size()};

    // clang-format off
    ArrayList<int, PagedBlock> array = {
        ProxyAlloc<PoolAlloc> {alloc, g_KiB}, 100, 5
    };
    // clang-format on

    array.insert(10, g_max_isize);

    array.for_each(Action {[](int& x, usize i, const ArrayList<int, PagedBlock>& self) {
        if ( i == 0 )
            printf("{\n");

        printf("  %2lu | %i\n", i, x);

        if ( i + 1 == self.count() )
            printf("}\n");
    }});

    Action func = {[](const int& a, const int& b) {
        return a >= b;
    }};

    array.remove(g_min_isize);

    array.for_each(Action {[](int& x, usize i, const ArrayList<int, PagedBlock>& self) {
        if ( i == 0 )
            printf("{\n");

        printf("  %2lu | %i\n", i, x);

        if ( i + 1 == self.count() )
            printf("}\n");
    }});

    if ( array.contains(0, func) )
        printf("Array contains x >= 0\n");

    array.clear(Action {[](int x, usize i) {
        destroy(x);
    }});

    return 0;
}
