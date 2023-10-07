#include <smal/Struct/import.hpp>

int
main(int argc, const char* argv[])
{
    long mem = 1024 * 1024l;
    long pag = 1024 * 2l;

    smal::PageAlloc origin = {malloc(mem), mem, pag};

    smal::Vector<void*> vec;

    vec = smal::PagedArray<void*> {origin, 32};

    for ( long i = 0; i < vec.length(); i++ )
        printf("%p\n", vec[i]);

    return 0;
}
