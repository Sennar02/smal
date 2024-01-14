#include <smal/Algo/import.hpp>
#include <time.h>

using namespace ma;

int
main(int argc, const char* argv[])
{
    DummyOrigin            origin;
    HashTable<String, u32> table = {origin, 8u};

    srand(time(0));

    for ( u32 i = 0; i < argc - 1u; i++ )
        table.insert(argv[i + 1u], rand() % 256);

    for ( u32 i = 0; i < 5u; i++ ) {
        table.forEach([](u32& x, const String& y) {
            printf("%s -> %u\n", y.memory(), x += 3);
        });

        printf("\n");
    }

    return 0;
}
