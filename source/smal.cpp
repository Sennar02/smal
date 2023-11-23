#include <smal/Memory/import.hpp>

using namespace ma;

static const i32 g_buff_size         = 2048;
static char      g_buff[g_buff_size] = {0};

class ScenesReader
{
public:
    static usize
    read(const char* name)
    {
        auto& reader = s_reader;
        File  stream = {name};

        auto func = [&reader](auto& stream) {
            auto r = reader.read(stream);

            if ( r > 0 && r < g_buff_size - 1 )
                printf("%s", reader.memory());
        };

        stream.call(FileMode::Read, func);

        return 0;
    }

private:
    inline static FileReader s_reader =
        {g_buff, g_buff_size};
};

int
main(int argc, const char* argv[])
{
    return ScenesReader::read("../assets/scenes.json");
}
