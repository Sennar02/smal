#include <smal/Common/File/FileIStream.hpp>

#include <stdio.h> // fopen, fclose, fread

namespace ma
{
    static const char* g_file_mode = "r";

    FileIStream::FileIStream()
        : m_source {0}
    { }

    FileIStream::FileIStream(String name)
        : m_source {0}
    {
        open(name);
    }

    bool
    FileIStream::open(String name)
    {
        if ( m_source == 0 ) {
            m_source = fopen(name.memory(), g_file_mode);

            if ( m_source != 0 )
                return true;
        }

        return false;
    }

    bool
    FileIStream::close()
    {
        auto* source = (FILE*) m_source;

        if ( m_source != 0 )
            return fclose(source) == 0;

        return true;
    }

    u32
    FileIStream::read(char* memory, u32 size)
    {
        auto* source = (FILE*) m_source;

        if ( memory != 0 )
            return fread(memory, 1, size, source);

        return g_max_u32;
    }
} // namespace ma
