#include <smal/Engine/import.hpp>
#include <screen.hpp>
#include <loader.hpp>

static const usize size = 128;
static const usize page = 1024 * 4;

static char* memory = 0;

int
main(int argc, const char* argv[])
{
    memory = (char*) calloc(size, page);

    char  buffer[4096] = {0};
    usize length       = 0;

    {
        PoolOrigin pool = {memory, size * page, page};
        Engine     game = {&pool, 32};
        Loader     load = {&pool};

        auto* file = fopen("../assets/machine.json", "r");

        if ( file != 0 )
            length = fread(buffer, 1, 4096, file);

        printf("\x1b[32m%s\x1b[0m", buffer);

        String json = {buffer, length};

        Json::Reader::read(load, json);

        printf("Definitions:\n");
        printf(" - Names:\n");
        load.names.for_each([](auto& key, auto& val) {
            printf("   - %10s | %u\n", key.memory(), val);
        });

        printf(" - Exits:\n");
        load.exits.for_each([](auto& str, auto& val) {
            printf("   - %10s | %u\n", str.memory(), val);
        });

        game.screens().insert(load.names["Title"], new TitleScreen {load.names, load.exits});
        game.screens().insert(load.names["Level"], new LevelScreen {load.names, load.exits});
        game.screens().insert(load.names["Exit"], new ExitScreen {load.names, load.exits});

        printf("Transitions:\n");
        load.table.for_each([&game](auto& val, usize idx) {
            printf(" - %4u:%05u | %u\n", val.active, val.exit, val.coming);

            game.screens().insert(
                val.active,
                val.exit,
                val.coming);
        });

        if ( game.is_active() )
            game.loop(load.names["Title"]);
    }

    return 0;
}

namespace ma
{
    template <>
    usize
    hash(const String& value)
    {
        return hash(value.memory());
    }
} // namespace ma
