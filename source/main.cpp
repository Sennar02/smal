#include <smal/Entity/import.hpp>

struct Vec2f
{
    float x;
    float y;
};

Vec2f
nrm(const Vec2f& vec)
{
    float mag = sqrt(vec.x * vec.x +
                     vec.y * vec.y);

    return {
        .x = vec.x / mag,
        .y = vec.y / mag,
    };
}

struct Pos : public Vec2f
{ };

struct Vel : public Vec2f
{
    Vel(float x, float y, float mag)
        : Vec2f(nrm({x, y}))
        , mag {mag}
    { }

    float mag;
};

int
main(int argc, const char* argv[])

{
    long mem = 1024 * 1024l;
    long pag = 1024 * 2l;

    smal::PageAlloc origin = {malloc(mem), mem, pag};

    smal::Vector<void*, smal::PagedArray>  vec = {{origin}};
    smal::SparseMap<Pos, smal::PagedArray> pos = {origin, {origin}};
    smal::SparseMap<Vel, smal::PagedArray> vel = {origin, {origin}};

    vec.insert((void*) &pos);
    vec.insert((void*) &vel);

    smal::AttribMng manager = {vec};

    manager.give<Pos, Vel>(0,
        {0, 0},
        {1, 1, 4});

    while ( manager.has<Pos, Vel>(0) ) {
        Pos& pos = manager.get<Pos>(0);
        Vel& vel = manager.get<Vel>(0);

        pos.x += vel.x * vel.mag;
        pos.y += vel.y * vel.mag;

        printf("%f, %f\n", pos.x, pos.y);
        if ( pos.x > 1000.f )
            manager.take<Pos, Vel>(0);
    }

    return 0;
}
