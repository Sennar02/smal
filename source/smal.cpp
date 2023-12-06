#include <smal/Json/import.hpp>
#include <stdio.h>

using namespace ma;

static auto g_memory =
    MemoryService {g_MiB * 64};

int
main(int argc, const char* argv[])
{
    PoolAlloc alloc = g_memory.create<PoolAlloc>(
        g_MiB * 63, g_KiB * 4);

    JsonDict json = {alloc, 10};

    for ( i32 i = 1; i < argc; i++ )
        json.insert({argv[i]}, {i});

    json.forEach([](const String& prop, JsonValue& item) {
        printf("[%s] -> ", prop.memory());

        if ( item.isNumber() )
            printf("%u", item.toUnsig());

        printf("\n");
    });

    return 0;
}
