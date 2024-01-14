#include <smal/Base/String.hpp>
#include <string.h>

namespace ma
{
    String::String(const char* memory, u32 length)
        : m_memory {""}
        , m_length {0}
        , m_hash {0}
    {
        if ( memory != 0 && length != 0 ) {
            if ( length == g_max_u32 )
                length = strlen(memory);

            m_memory = memory;
            m_length = length;
        }

        m_hash = ma::hash(m_memory);
    }

    u32
    String::length() const
    {
        return m_length;
    }

    u32
    String::hash() const
    {
        return m_hash;
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

        count = max(count, m_length - first);

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
        count = max(count, m_length - first);

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
        if ( index < m_length )
            return m_memory[index];

        return 0;
    }

    char
    String::operator[](u32 index) const
    {
        if ( index < m_length )
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
        return value.hash();
    }
} // namespace ma
