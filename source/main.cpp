#include <smal/Entity/import.hpp>

struct Pos
{
    float x;
    float y;
};

struct Vel
{
    float x;
    float y;
    float prc;
    float mag;
};

int
main(int argc, const char* argv[])
{
    long mem = 1024 * 1024l;
    long pag = 1024 * 2l;

    smal::PageAlloc  origin = {malloc(mem), mem, pag};
    smal::CmpHolder managr = {origin};

    smal::SparseTable<Pos> spos = {{origin}, {origin}, {origin}};
    smal::SparseTable<Vel> svel = {{origin}, {origin}, {origin}};

    spos.resize(32, 32);
    svel.resize(32, 32);

    managr.pools().resize(32);
    managr.pools()[managr.number<Pos>()] = &spos;
    managr.pools()[managr.number<Vel>()] = &svel;

    managr.give<Vel, Pos>(0,
        {0, 0, 0, 0},
        {0, 0});

    if ( managr.has<Pos, Vel>(10) ) {
        auto& pos = managr.get<Pos>(10);
        auto& vel = managr.get<Vel>(10);

        printf("Entity { 10 }:\n");
        printf("- Pos { %.3f, %.3f }\n", pos.x, pos.y);
        printf("- Vel { %.3f, %.3f }\n", vel.x, vel.y);

        managr.take<Pos>(10);
    }

    printf("%i\n", managr.has<Vel>(0));

    return 0;
}
