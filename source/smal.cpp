#include <smal/Json/import.hpp>
#include <stdio.h>

using namespace ma;

static u32  size       = 2048;
static char buff[2048] = {0};

int
main(int argc, const char* argv[])
{
    auto  alloc = PoolAlloc {buff, size, 64};
    char* addr  = 0;
    char* pntr;

    addr = alloc.acquire();
    pntr = alloc.acquire();

    alloc.release(addr);
    alloc.release(pntr);
    alloc.release(addr);

    return 0;
}
