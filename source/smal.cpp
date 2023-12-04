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
        printf("[value | \"");

        for ( u32 i = 0; i < value.size(); i++ )
            printf("%c", value[i]);

        printf("\"]\n");

        return true;
    }

    bool
    number(u32 value)
    {
        printf("[value | %u]\n", value);

        return true;
    }

    bool
    number(i32 value)
    {
        printf("[value | %i]\n", value);

        return true;
    }

    bool
    number(f32 value)
    {
        printf("[value | %f]\n", value);

        return true;
    }

    bool
    boolean(bool value)
    {
        if ( value == true )
            printf("[value | true]\n");
        else
            printf("[value | false]\n");

        return true;
    }

    bool
    null()
    {
        printf("[value | null]\n");

        return true;
    }

    bool
    arrOpen(u32 depth)
    {
        printf("[arrop | depth %u]\n", depth);

        return true;
    }

    bool
    arrClose(u32 depth, u32 count)
    {
        printf("[arrcl | depth %u, count %u]\n", depth, count);

        return true;
    }

    bool
    objOpen(u32 depth)
    {
        printf("[objop | depth %u]\n", depth);

        return true;
    }

    bool
    objClose(u32 depth, u32 count)
    {
        printf("[objcl | depth %u, count %u]\n", depth, count);

        return true;
    }

    bool
    objLabel(const String label)
    {
        printf("[label | \"");

        for ( u32 i = 0; i < label.size(); i++ )
            printf("%c", label[i]);

        printf("\"]\n");
        return true;
    }
};

static auto g_memory =
    MemoryService {g_MiB * 64};

void
print(int& x, u32 i, u32 c)
{
    if ( i == 0 )
        printf("{\n");

    printf("  %02u: %i\n", i, x);

    if ( i + 1 == c )
        printf("}\n");
}

int
main(int argc, const char* argv[])
{
    Handler    hdlr;
    JsonReader json;

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

    ArrayList<int, PagedBlock> list = {pool, 10, 5};

    list.forEach([](int& x, u32 i, u32 c) {
        x = i + 1;
    });

    list.insert(10, g_max_u32);

    list.forEach(action<print>());

    Action func = {[](const int& a, const int& b) {
        return a >= b;
    }};

    list.remove(0);

    list.forEach(Action {
        bind<print>,
    });

    if ( list.contains(10, func) )
        printf("list has item >= 10\n");

    list.clear(
        action([](int& x) {
            printf("%i\n", x);
        }));

    return 0;
}
