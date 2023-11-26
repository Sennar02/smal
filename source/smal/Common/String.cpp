#include <smal/Common/String.hpp>
#include <smal/Common/math.hpp>

#include <string.h> // strlen

namespace ma
{
    String::String(const char* memory, usize size)
        : m_memory {memory}
        , m_size {size}
    {
        if ( m_memory == 0 ) m_memory = "";

        if ( m_size == g_max_usize )
            m_size = strlen(m_memory);
    }

    usize
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
    String::equals(const String& other, usize count, usize first) const
    {
        char a = 0, b = 0;

        if ( count == g_max_usize )
            count = m_size - first;

        for ( usize i = first; i < count; i++ ) {
            a = m_memory[i];
            b = other.m_memory[i];

            if ( a == 0 || a != b )
                break;
        }

        return a == b;
    }

    bool
    String::contains(char byte, usize count, usize first) const
    {
        if ( count == g_max_usize )
            count = m_size - first;

        for ( usize i = first; i < count; i++ ) {
            if ( m_memory[i] == byte )
                return true;
        }

        return false;
    }

    bool
    String::operator==(const String& other) const
    {
        return equals(other);
    }

    template <>
    usize
    hash(const String& value)
    {
        const char* string =
            value.memory();

        return hash(string);
    }
} // namespace ma
