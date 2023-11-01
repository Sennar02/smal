#include <smal/Struct/import.hpp>

static const ma::usize buflen = 8192;
static const ma::usize paglen = 1024;

static char buffer[buflen] = {0};

namespace ma
{
    template <class Type>
    using Each = ma::Func<void(const Type&, usize)>;
} // namespace ma

int
main(int argc, const char* argv[])
{
    ma::PoolOrigin                   pool = {buffer, buflen, paglen};
    ma::ArrayList<ma::u32>           list = {&pool, 10};
    ma::ArrayList<ma::Each<ma::u32>> each = {&pool, 10};

    auto comp = [](const ma::u32& value, const ma::u32& other) {
        return value < other;
    };

    auto mul = ma::func([](const ma::u32& v, ma::usize i) {
        printf("%lu\n", i * v);
    });

    auto sum = ma::func([](const ma::u32& v, ma::usize i) {
        printf("%lu\n", i + v);
    });

    for ( int i = 0; i < 10; i++ )
        list.insert(rand() % 100);

    each.insert(mul);
    each.insert(sum);

    list.for_each([&list](auto& v, auto i) {
        printf("%lu | %u\n", i, v);

        if ( list.count() == i + 1 )
            printf("\n");
    });

    list.sort<ma::QuickSort>(comp);

    list.for_each([&list](auto& v, auto i) {
        printf("%lu | %u\n", i, v);

        if ( list.count() == i + 1 )
            printf("\n");
    });

    for ( ma::usize i = 0; i < each.count(); i++ ) {
        list.for_each(each[i]);

        if ( i + 1 != each.count() )
            printf("\n");
    }

    return 0;
}
