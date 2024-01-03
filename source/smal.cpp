#include <smal/Signal/import.hpp>
#include <time.h>

using namespace ma;

int
main(int argc, const char* argv[])
{
    ArrayStack<u32> stack = {g_origin, 256u};

    stack.insert(0);
    stack.insert(1);
    stack.insert(2);

    while ( stack.isEmpty() == false ) {
        stack.forEach([](auto& x, auto, auto) {
            printf("%u\n", x);
        });

        stack.remove();

        if ( stack.count() != 0 )
            printf("\n");
    }

    return 0;
}
