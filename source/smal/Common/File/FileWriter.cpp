#include <smal/Common/File/FileWriter.hpp>
#include <smal/Common/File/FileOStream.hpp>

namespace ma
{
    FileWriter::FileWriter()
    { }

    usize
    FileWriter::write(FileOStream& stream, const String& string)
    {
        const char* mem = string.memory();
        usize       siz = string.size();

        if ( string.size() != 0 )
            return stream.write(mem, siz);

        return g_max_usize;
    }
} // namespace ma
