#include <smal/Base/File/FileWriter.hpp>
#include <smal/Base/File/FileOStream.hpp>

namespace ma
{
    FileWriter::FileWriter()
    { }

    u32
    FileWriter::write(FileOStream& stream, const String& string)
    {
        const char* addr = string.memory();
        u32         size = string.size();

        if ( string.size() != 0 )
            return stream.write(addr, size);

        return g_max_u32;
    }
} // namespace ma
