#include <smal/Entity/import.hpp>

using smal::usize;
using smal::f32;

struct Pos
{
    f32 x, y;
};

static const usize g_zone = 1024 * 1024 * 8;
static const usize g_pool = 1024 * 1024 * 1; // 1016;
static const usize g_page = 1024 * 16;

int
main(int argc, const char* argv[])
{
    char* memory = (char*) calloc(1, g_pool);

    {
        smal::PoolOrigin pool = {memory, g_pool, g_page};

        smal::Holder<smal::SparseMap> holder = {&pool};
        smal::SparseMap<Pos>          pos    = {&pool};

        holder.give(&pos);

        for ( usize i = 0; i < 100'000; i++ )
            holder.give<Pos>(i, {(f32) i, (f32) i});

        if ( holder.has<Pos>() ) {
            auto& pool = *holder.find<Pos>();

            while ( pool.size() > 0 ) {
                printf("%lu\n", pool.size());

                for ( usize i = 0; i < pool.size(); i++ ) {
                    auto& p = holder.find<Pos>(i);

                    p.x += 1;
                    p.y += 1;
                }

                holder.take<Pos>(pool.size() - 1);
            }
        }
    }

    free(memory);

    return 0;
}
