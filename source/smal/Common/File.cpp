#include <smal/Common/File.hpp>

namespace ma
{
    static const char* g_file_modes[] = {
        "r", // Read
        "a", // WritePast
        "w", // WriteWipe
    };

    File::File(String name)
        : m_name {name}
        , m_file {0}
        , m_mode {FileMode::SIZE}
        , m_open {false}
    { }

    bool
    File::is_open() const
    {
        return m_open;
    }

    bool
    File::is_open(FileMode mode) const
    {
        if ( m_open )
            return mode == m_mode;

        return false;
    }

    String
    File::name() const
    {
        if ( m_open )
            return m_name;

        return {};
    }

    File&
    File::open(FileMode mode, String name)
    {
        FILE* file = 0;

        if ( m_mode == FileMode::SIZE ) m_mode = mode;
        if ( m_name == String {} ) m_name = name;

        if ( m_mode != FileMode::SIZE ) {
            if ( m_open == false ) {
                file = fopen(m_name.memory(), g_file_modes[(u8) mode]);

                if ( file != 0 ) {
                    m_file = file;
                    m_open = true;
                }
            }
        }

        return *this;
    }

    File&
    File::close()
    {
        if ( m_open == true ) {
            if ( fclose(m_file) == 0 ) {
                m_file = 0;
                m_mode = FileMode::SIZE;
                m_open = false;
            }
        }

        return *this;
    }

    usize
    File::read(char* memory, usize size)
    {
        if ( memory != 0 )
            return fread(memory, 1, size, m_file);

        return g_max_usize;
    }

    usize
    File::write(const char* memory, usize size)
    {
        if ( memory != 0 )
            return fwrite(memory, 1, size, m_file);

        return g_max_usize;
    }
} // namespace ma
