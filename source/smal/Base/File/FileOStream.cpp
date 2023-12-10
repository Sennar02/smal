#include <smal/Base/File/FileOStream.hpp>

#include <stdio.h> // fopen, fclose, fwrite

namespace ma
{
    static const char* g_file_mode = "a";

    FileOStream::FileOStream()
        : m_source {0}
    { }

    FileOStream::FileOStream(String name)
        : m_source {0}
    {
        open(name);
    }

    bool
    FileOStream::open(String name)
    {
        if ( m_source == 0 ) {
            m_source = fopen(name.memory(), g_file_mode);

            if ( m_source != 0 )
                return true;
        }

        return false;
    }

    bool
    FileOStream::close()
    {
        auto* source = (FILE*) m_source;

        if ( m_source != 0 )
            return fclose(source) == 0;

        return true;
    }

    u32
    FileOStream::write(const char* memory, u32 size)
    {
        auto* source = (FILE*) m_source;

        if ( memory != 0 )
            return fwrite(memory, 1, size, source);

        return g_max_u32;
    }
} // namespace ma
