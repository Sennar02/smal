#include <smal/Entity/import.hpp>

static const long memlen = 1024 * 1024l;
static const long paglen = 1024 * 2l;

int
main(int argc, const char* argv[])
{
    void* memptr = calloc(1, memlen);

    smal::PageAlloc                       origin = {memptr, memlen, paglen};
    smal::AttribHolder<smal::SparseTable> attrib = {origin};

    srand(time(0));

    if ( attrib.contains<int>() == false )
        attrib.insert<int>(new smal::SparseTable<int> {
            {origin},
            {origin},
            {origin},
        });

    if ( attrib.contains<int>() == true ) {
        auto& pool = attrib.find<int>();

        for ( long i = 0; i < 15; i++ )
            pool.insert(rand() % 100, rand() % 100);

        for ( long i = 0; i < pool.size(); i++ )
            printf("%i\n", pool[i]);
    }

    return 0;
}
