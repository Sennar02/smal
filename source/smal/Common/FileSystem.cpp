#include <smal/Common/FileSystem.hpp>
#include <smal/Common/File.hpp>

namespace ma
{
    bool
    FileSystem::exists(String name)
    {
        FILE* file = fopen(name.memory(), "wx");

        if ( file != 0 )
            return fclose(file) == 0;

        return false;
    }

    File
    FileSystem::create(String name)
    {
        FILE* file = fopen(name.memory(), "wx");

        if ( file != 0 )
            fclose(file);

        return {name};
    }

    bool
    FileSystem::destroy(String name)
    {
        if ( remove(name.memory()) == 0 )
            return true;

        return false;
    }
} // namespace ma
