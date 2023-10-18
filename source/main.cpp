#include <smal/Struct/import.hpp>
#include <iostream>

using smal::usize;
using smal::f32;

class Vector2
{
public:
    f32 x;
    f32 y;
};

static const usize g_zone = 1024 * 1024 * 8;
static const usize g_pool = 1024 * 1024 * 1; // 1016;
static const usize g_page = 1024 * 4;

int
main(int argc, const char* argv[])
{
    char*     memory = (char*) calloc(1, g_pool);
    const f32 number = 50'000;

    {
        smal::PoolOrigin         pool = {memory, g_pool, g_page};
        smal::SparseMap<Vector2> map  = {&pool};

        map.resize(number, number);

        for ( f32 i = 0; i < number; i++ ) {
            f32     idx = {number - 1 - i};
            Vector2 vec = {idx, idx};

            if ( map.insert(idx, vec) == false )
                break;
        }

        map.sort<smal::QuickSort>([](auto& a, auto& b) {
            return a < b;
        });
    }

    free(memory);

    return 0;
}
