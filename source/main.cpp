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

    smal::PageAlloc origin = {malloc(mem), mem, pag};

    smal::CompHolder       holder = {origin};
    smal::SparseTable<Pos> spos   = {{origin}, {origin}, {origin}};
    smal::SparseTable<Vel> svel   = {{origin}, {origin}, {origin}};

    spos.resize(32, 32);
    svel.resize(32, 32);

    holder.pools().resize(32);
    holder.pools()[holder.number<Pos>()] = &spos;
    holder.pools()[holder.number<Vel>()] = &svel;

    holder.give<Vel, Pos>(0,
        {0, 0, 0, 0},
        {0, 0});

    if ( holder.has<Pos, Vel>(10) )
        printf("Entity { 10 } has pos and vel\nn");
    else {
        if ( holder.has<Pos>(10) ) {
            auto& pos = holder.get<Pos>(10);

            printf("Entity { 10 } has pos = {%f, %f}\n",
                pos.x,
                pos.y);

            holder.take<Pos>(10);
        }
    }

    return 0;
}
