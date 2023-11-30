#include <smal/Common/File/FileWriter.hpp>
#include <smal/Common/File/FileOStream.hpp>

namespace ma
{
    FileWriter::FileWriter()
    { }

    u32
    FileWriter::write(FileOStream& stream, const String& string)
    {
        const char* mem = string.memory();
        u32       siz = string.size();

        if ( string.size() != 0 )
            return stream.write(mem, siz);

        return g_max_u32;
    }
} // namespace ma
