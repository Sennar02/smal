#include <smal/Common/String.hpp>
#include <smal/Common/helper.hpp>

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
        char c1 = 0;
        char c2 = 0;

        if ( count == g_max_usize )
            count = m_size - first;

        for ( usize i = first; i < count; i++ ) {
            c1 = m_memory[i];
            c2 = other.m_memory[i];

            if ( c1 == 0 || c1 != c2 )
                break;
        }

        return c1 == c2;
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
    Math::hash(const String& value)
    {
        return hash<const char*>(value.memory());
    }
} // namespace ma
