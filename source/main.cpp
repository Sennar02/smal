#include <smal/Struct/import.hpp>

static const long memlen = 1024 * 1024 * 1024l;
static const long paglen = 1024 * 8l;

int
main(int argc, const char* argv[])
{
    void* memptr = calloc(1, memlen);

    {
        smal::PageAlloc   origin = {memptr, memlen, paglen};
        smal::Vector<int> vector = {origin};

        vector.resize(1'000'000l);

        printf("%li\n", vector.length());

        for ( long i = 0; i < vector.length(); i++ )
            vector[i] = i;
    }

    free(memptr);

    return 0;
}
