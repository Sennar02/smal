#include <smal/Struct/import.hpp>

namespace app
{
    using namespace ma;

    static const usize size = 8192;
    static const usize page = 512;

    static char memory[size] = {0};
} // namespace app

int
main(int argc, const char* argv[])
{
    using namespace app;

    PoolOrigin        pool = {memory, size, page};
    HashMap<u32, u32> nums = {&pool, 32};

    for ( ma::usize i = 0; i < nums.size(); i++ )
        nums.insert(i, rand() % 1000);

    if ( nums.contains(0) == false )
        printf("Map: Doesn't contain 0\n");
    else
        printf("Map: Does contain 0\n");

    nums.for_each([&nums](auto& iden, auto& value) {
        printf("Map: %2u | %3u\n", iden, value);

        if ( iden + 1 == nums.size() )
            printf("Map: Finish\n");
    });

    return 0;
}
