#include <smal/Entity/import.hpp>

using smal::usize;
using smal::f32;

struct Pos
{
    f32 x, y;
};

static const usize g_pool = 1024 * 1024 * 16;
static const usize g_page = 1024 * 16;

static const usize g_numb = 10;

int
main(int argc, const char* argv[])
{
    char* memory = (char*) calloc(1, g_pool);

    {
        smal::PoolOrigin pool = {memory, g_pool, g_page};

        smal::Holder<smal::SparseMap> holder = {&pool};
        smal::SparseMap<Pos>          pos    = {&pool};

        holder.give(&pos);

        pos.resize(g_numb, g_numb);

        for ( usize i = 0; i < g_numb; i++ )
            holder.give<Pos>(g_numb - 1 - i, {(f32) i, (f32) i});

        if ( holder.has<Pos>() ) {
            auto& pool = *holder.find<Pos>();

            for ( usize i = 0; i < pool.size(); i++ ) {
                auto& pi = pool[i];
                auto& pk = pool[pool.indexOf(i)];

                // clang-format off
                printf("<%2.3f, %2.3f> vs <%2.3f, %2.3f>\n",
                    pi.x, pi.y, pk.x, pk.y);
                // clang-format on
            }
        }
    }

    free(memory);

    return 0;
}
