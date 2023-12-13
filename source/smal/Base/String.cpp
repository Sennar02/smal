#include <smal/Base/String.hpp>
#include <smal/Base/math.hpp>

#include <string.h> // strlen

namespace ma
{
    String::String(const char* memory, u32 size)
        : m_memory {memory}
        , m_size {size}
    {
        if ( m_memory == 0 ) m_memory = "";

        if ( m_size == g_max_u32 )
            m_size = strlen(m_memory);
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
        char a = 0, b = 0;

        if ( count == g_max_u32 )
            count = m_size - first;

        for ( u32 i = first; i < count; i++ ) {
            a = m_memory[i];
            b = that.m_memory[i];

            if ( a == 0 || a != b )
                break;
        }

        return a == b;
    }

    bool
    String::contains(char byte, u32 count, u32 first) const
    {
        if ( count == g_max_u32 )
            count = m_size - first;

        for ( u32 i = first; i < count; i++ ) {
            if ( m_memory[i] == byte )
                return true;
        }

        return false;
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
        return equals(that);
    }

    template <>
    u32
    hash(const String& value)
    {
        return hash(value.memory());
    }
} // namespace ma