#include <stdio.h>
#include <smal/Memory/import.hpp>

using namespace smal;

int
main(int argc, const char* argv[])
{
    char      buffer[1024] = {0};
    PageAlloc origin       = {buffer, 128, 32};

    Page p0 = origin.reserve();
    Page p1 = origin.reserve();
    Page p2 = origin.reserve();

    PageTable table = {
        p0.get_memory(),
        p0.get_length(),
    };

    table.insert(p1, 0);
    table.insert(p2, 32);

    for ( long i = 0; i < 65; i++ ) {
        auto t = table.lookup(i);

        printf("%p, %li\n",
            t.get<0>(),
            t.get<1>());
    }

    return 0;
}
