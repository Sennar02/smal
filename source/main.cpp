#include <smal/Struct/import.hpp>

using smal::usize;
using smal::f32;

struct Position
{
    f32 x;
    f32 y;

    bool
    operator==(const Position& other) const
    {
        return this->x == other.x &&
               this->y == other.y;
    }
};

static const usize g_zone = 1024 * 1024 * 8;
static const usize g_pool = 1024 * 1024 * 1016;
static const usize g_page = 1024 * 2;

namespace smal
{
    template <class Type>
    using FixedList = ArrayList<Type, FixedArray>;
} // namespace smal

int
main(int argc, const char* argv[])
{
    char* memory = (char*) calloc(1, g_zone + g_pool);

    {
        smal::PoolOrigin  pool = {memory, g_pool, g_page};
        smal::StackOrigin zone = {memory + g_pool, g_zone};

        smal::FixedList<Position> list = {&pool};

        list.insert({2, 2}, -3);
        list.insert({0, 0});
        list.insert({1, 1}, 0);
        list.remove(-3);

        list.sort<smal::QuickSort>([](auto& a, auto& b) {
            return a.x < b.x;
        });

        list.forEach([](const auto& a, usize i) {
            printf("%lu => %.3f, %.3f\n", i, a.x, a.y);
        });

        auto copy = list.clone(&pool);

        copy.forEach([](const auto& a, usize i) {
            printf("%lu => %.3f, %.3f\n", i, a.x, a.y);
        });

        printf("%li\n", list.indexOf({2, 2}, [](auto& a, auto& b) {
            return a.x == b.x;
        }));
    }

    free(memory);

    return 0;
}
