#include <smal/Struct/import.hpp>

int
main(int argc, const char* argv[])
{
    long mem = 1024 * 1024l;
    long pag = 1024 * 2l;

    smal::PageAlloc origin = {malloc(mem), mem, pag};

    smal::Vector<int, smal::PagedArray> vec = {
        smal::PagedArray<int> {origin},
    };

    vec.resize(16);
    vec.insert(1);

    for ( long i = 0; i < vec.size(); i++ )
        printf("%i\n", vec[i]);

    return 0;
}
