#include <smal/Entity/import.hpp>

static const long size = 1024 * 1024 * 4;
static const long page = 1024 * 4;

int
main(int argc, const char* argv[])
{
    char* buff = (char*) calloc(1, size);

    smal::PoolOrigin origin = {buff, size, page};

    {
        smal::SparseMap<long> longs  = {&origin};
        smal::Holder          holder = {&origin};
        smal::Status          status = {&origin};

        if ( holder.give(&longs) == false )
            return 1;

        smal::Entity entity;

        printf("entity = %lu\n", entity.identif());

        if ( entity.create(status) ) {
            printf("entity = %lu\n", entity.identif());

            if ( entity.give<long>(holder, -1) )
                printf("attrib = %li\n", entity.find<long>(holder));

            if ( entity.destroy(status) )
                printf("entity = %lu\n", entity.identif());

            // Segfaults
            // entity.find<long>(holder);
        }
    }

    free(buff);
    return 0;
}
