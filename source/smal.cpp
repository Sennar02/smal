#include <smal/Struct/import.hpp>

static const ma::usize buflen = 8192;
static const ma::usize paglen = 1024;

static char buffer[buflen] = {0};

int
main(int argc, const char* argv[])
{
    ma::PoolOrigin         pool = {buffer, buflen, paglen};
    ma::ArrayList<ma::f32> list = {&pool, 10};

    list.insert(0);

    list.for_each([](auto& e, auto i) {
        printf("%f\n", e);
    });

    return 0;
}
