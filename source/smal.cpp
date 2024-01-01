#include <smal/Signal/import.hpp>
#include <time.h>

using namespace ma;

int
main(int argc, const char* argv[])
{
    HashTable<u32, Tuple<u32, u32, u32>> table = {g_origin, 256u};

    table.insert(0, {1, 2, 3});
    table.insert(1, {2, 4, 6});
    table.insert(2, {3, 6, 9});

    auto& x = table.find(0);

    printf("0, %u\n", x.extract<0>());

    table.forEach([](const u32& x, Tuple<u32, u32, u32>& y) {
        printf("%u -> %u\n", x, y.extract<0>());
    });

    return 0;
}
