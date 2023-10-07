#include <smal/Struct/import.hpp>

struct Pos
{
    float x;
    float y;
};

int
main(int argc, const char* argv[])
{
    long mem = 1024 * 1024l;
    long pag = 1024 * 2l;

    smal::PageAlloc origin = {malloc(mem), mem, pag};

    smal::SparseSet<Pos, smal::PagedArray> set = {
        {origin},
        {origin},
        {origin},
    };

    set.resize(1, 1);
    set.insert(0, {0, 0});

    for ( long i = 0; i < set.size(); i++ )
        printf("%f, %f\n",
            set[i].x,
            set[i].y);

    return 0;
}
