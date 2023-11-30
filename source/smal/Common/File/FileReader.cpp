#include <smal/Common/File/FileReader.hpp>
#include <smal/Common/File/FileIStream.hpp>

namespace ma
{
    FileReader::FileReader(char* memory, u32 size)
        : m_memory {memory}
        , m_size {size - 1}
        , m_count {0}
    {
        if ( m_size == g_max_u32 )
            m_size = 0;
    }

    u32
    FileReader::size() const
    {
        return m_size;
    }

    u32
    FileReader::count() const
    {
        return m_count;
    }

    const char*
    FileReader::memory() const
    {
        return m_memory;
    }

    String
    FileReader::string() const
    {
        return {m_memory, m_count};
    }

    u32
    FileReader::read(FileIStream& stream)
    {
        if ( m_memory != 0 && m_size != 0 ) {
            m_count = stream.read(m_memory, m_size);

            if ( m_count != g_max_u32 )
                m_memory[m_count] = 0;
        }

        return m_count;
    }
} // namespace ma
