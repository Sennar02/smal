#include <stdio.h>
#include <smal/Common/import.hpp>

int
main(int argc, const char* argv[])
{
    smal::Tuple<int> t;

    t.get<0>() = 10;

    if ( t.get<0>() == 0 )
        printf("t = <0>\n");
    else
        printf("t = <?>\n");

    return 0;
}
