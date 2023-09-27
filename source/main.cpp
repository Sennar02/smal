#include <stdio.h>
#include <smal/Memory/import.hpp>

using namespace smal;

int
main(int argc, const char* argv[])
{
    char      buffer[1024] = {0};
    PageAlloc origin       = {buffer, 256, 32};

    Page p0 = origin.reserve();
    Page p1 = origin.reserve();
    Page p2 = origin.reserve();
    Page p3 = {0, buffer + 256, 8};

    PageTable table = {p0.get_memory(), p0.get_length()};

    printf("Page table:\n");

    table.insert(p1, 0);
    table.insert(p2, 32);
    table.remove(p1);
    table.insert(p3, 0);

    for ( long i = 0; i < table.m_size; i++ ) {
        printf("\t%3li. <[%p, %p), %li>\n",
            i,
            table.m_memory[i].memory,
            table.m_memory[i].memory + table.m_memory[i].length,
            table.m_memory[i].offset);
    }

    for ( long i = 0; i < 70; i++ ) {
        auto t = table.lookup(i);

        printf("%p, %li\n",
            t.get<0>(),
            t.get<1>());
    }

    return 0;
}
