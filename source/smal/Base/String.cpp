#include <smal/Base/String.hpp>
#include <string.h> // strlen

namespace ma
{
    String::String(const char* memory, u32 size)
        : m_memory {""}
        , m_size {0}
    {
        if ( memory != 0 && size != 0 ) {
            if ( size == g_max_u32 )
                size = strlen(memory);

            m_memory = memory;
            m_size   = size;
        }
    }

    u32
    String::size() const
    {
        return m_size;
    }

    const char*
    String::memory() const
    {
        return m_memory;
    }

    bool
    String::equals(const String& that, u32 count, u32 first) const
    {
        char l = 0;
        char r = 0;

        count = max(count, m_size - first);

        for ( u32 i = first; i < count; i++ ) {
            l = m_memory[i];
            r = that.m_memory[i];

            if ( l == 0 || l != r )
                break;
        }

        return l == r;
    }

    bool
    String::equals(const String& that) const
    {
        return equals(that, g_max_u32);
    }

    bool
    String::contains(char byte, u32 count, u32 first) const
    {
        count = max(count, m_size - first);

        for ( u32 i = first; i < count; i++ ) {
            if ( m_memory[i] == byte )
                return true;
        }

        return false;
    }

    bool
    String::contains(char byte) const
    {
        return contains(byte, g_max_u32);
    }

    char
    String::operator[](u32 index)
    {
        if ( index < m_size )
            return m_memory[index];

        return 0;
    }

    char
    String::operator[](u32 index) const
    {
        if ( index < m_size )
            return m_memory[index];

        return 0;
    }

    bool
    String::operator==(const String& that) const
    {
        return equals(that, g_max_u32);
    }

    template <>
    u32
    hash(const String& value)
    {
        return hash(value.memory());
    }
} // namespace ma
