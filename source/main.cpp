#include <smal/Entity/import.hpp>

struct Pos
{
    float x;
    float y;
};

struct Vel
{
    float mag;
};

static const long memlen = 1024 * 1024l;
static const long paglen = 1024 * 2l;

int
main(int argc, const char* argv[])
{
    void* memptr = calloc(1, memlen);

    srand(time(0));

    {
        smal::PageAlloc  origin = {memptr, memlen, paglen};
        smal::Attributes attrib = {origin};

        smal::SparseTable<Pos, smal::PagedArray> sparse = {
            {origin},
            {origin},
            {origin},
        };

        attrib.holder().insert(&sparse);

        for ( long i = 0; i < 100; i++ ) {
            Pos pos = {
                .x = (rand() % 10'000) / 100.f,
                .y = (rand() % 10'000) / 100.f,
            };

            attrib.give<Pos>(i, pos);
        }

        if ( attrib.has<Pos>() == false )
            attrib.give<Pos>(0, {0, 0});

        if ( attrib.has<Vel>() == false )
            attrib.give<Vel>(0, {5.f});

        if ( attrib.has<Pos, Vel>() ) {
            auto& pos = attrib.get<Pos>();
            auto& vel = attrib.get<Vel>();

            long size = smal::Math::min(pos.size(), vel.size());

            for ( long f = 0; f < 1000; f++ ) {
                for ( long i = 0; i < size; i++ ) {
                    auto& p = pos.valueOf(i);
                    auto& v = vel.valueOf(i);

                    p.x += v.mag;
                    p.y += v.mag;

                    printf("%.3f, %.3f\n", p.x, p.y);
                }
            }
        } else
            printf("Missing <Pos> or <Vel>\n");
    }

    free(memptr);

    return 0;
}
