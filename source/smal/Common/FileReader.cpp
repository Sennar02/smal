#include <smal/Common/FileReader.hpp>
#include <smal/Common/FileIStream.hpp>

namespace ma
{
    FileReader::FileReader(char* memory, usize size)
        : m_memory {memory}
        , m_size {size - 1}
        , m_count {0}
    {
        if ( m_size == g_max_usize )
            m_size = 0;
    }

    usize
    FileReader::size() const
    {
        return m_size;
    }

    usize
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

    usize
    FileReader::read(FileIStream& stream)
    {
        if ( m_memory != 0 && m_size != 0 ) {
            m_count = stream.read(m_memory, m_size);

            if ( m_count != g_max_usize )
                m_memory[m_count] = 0;
        }

        return m_count;
    }
} // namespace ma
