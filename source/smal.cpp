#include <smal/Algo/import.hpp>
#include <smal/Signal/import.hpp>

using namespace ma;

class Random
{
public:
    Random(u32 seed)
        : m_sign {}
    {
        srand(seed);
    }

    SignalLink<u32>
    link()
    {
        return {m_sign};
    }

    void
    generate()
    {
        m_sign.publish(Tuple {(u32) rand()});
    }

private:
    Signal<u32> m_sign;
};

int
main(int argc, const char* argv[])
{
    Random        random = {0};
    Observer<u32> output = {[](u32 x) {
        printf("%u\n", x % 10);
    }};

    random.link().include(output);

    for ( u32 i = 0; i < 3; i++ )
        random.generate();

    return 0;
}
