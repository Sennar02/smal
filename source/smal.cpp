#include <smal/Struct/import.hpp>
#include <smal/Json/import.hpp>

#include <stdio.h>

using namespace ma;

class Handler
    : public BaseHandler
{
public:
    bool
    string(const String value)
    {
        printf("\"");

        for ( u32 i = 0; i < value.size(); i++ )
            printf("%c", value[i]);

        printf("\"\n");

        return true;
    }

    bool
    number(u32 value)
    {
        printf("%u\n", value);

        return true;
    }

    bool
    number(i32 value)
    {
        printf("%i\n", value);

        return true;
    }

    bool
    number(f32 value)
    {
        printf("%f\n", value);

        return true;
    }

    bool
    boolean(bool value)
    {
        if ( value == true )
            printf("true\n");
        else
            printf("false\n");

        return true;
    }

    bool
    null()
    {
        printf("null\n");

        return true;
    }

    bool
    arrOpen(u32 depth)
    {
        printf("[arr-open  depth %u]\n", depth);

        return true;
    }

    bool
    arrClose(u32 depth, u32 count)
    {
        printf("[arr-close depth %u, count %u]\n", depth, count);

        return true;
    }

    bool
    objOpen(u32 depth)
    {
        printf("[obj-open  depth %u]\n", depth);

        return true;
    }

    bool
    objClose(u32 depth, u32 count)
    {
        printf("[obj-close depth %u, count %u]\n", depth, count);

        return true;
    }

    bool
    objLabel(const String label)
    {
        printf("[label \"");

        for ( u32 i = 0; i < label.size(); i++ )
            printf("%c", label[i]);

        printf("\"]\n");
        return true;
    }
};

static auto g_memory =
    MemoryService {g_MiB * 64};

void
print(int& x, u32 i, const ArrayList<int, PagedBlock>& l)
{
    if ( i == 0 )
        printf("[\n");

    printf("  %2u: %i\n", i, x);

    if ( i + 1 == l.count() )
        printf("]\n");
}

int
main(int argc, const char* argv[])
{
    SyntaxHandler hdlr;
    JsonReader    json = {2};

    if ( argc == 2 ) {
        json.bind(hdlr);

        printf("\x1b[32m%s\x1b[0m\n", argv[1]);

        if ( json.read(argv[1]) == false )
            printf("<error>\n");
    }

    ChainAlloc chain = {
        g_memory.create<PoolAlloc>(g_MiB * 4, 8u),
        g_memory.create<PoolAlloc>(g_MiB * 8, 16u),
        g_memory.create<StackAlloc>(g_MiB * 4),
    };

    auto& stack = chain.alloc<2>();
    auto  avail = stack.avail();

    auto pool = PoolAlloc {stack.acquire(avail), avail, g_KiB};

    ArrayList<int, PagedBlock> array = {pool, 10, 5};

    printf("size = %u / %u\n",
        array.count(),
        array.size());

    printf("insert(%i, %li) = %i\n",
        10,
        g_max_i32,
        array.insert(10, g_max_i32));

    array.forEach(action<print>());

    Action func = {[](const int& a, const int& b) {
        return a >= b;
    }};

    printf("remove(%li) = %i\n",
        g_max_i32,
        array.remove(g_min_i32));

    array.forEach(Action {
        bind<print>,
    });

    if ( array.contains(10, 0, func) )
        printf("array has item >= 10\n");

    array.clear(
        action([](int& x) {
            printf("%i\n", x);
        }));

    return 0;
}
