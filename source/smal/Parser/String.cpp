#include <smal/Parser/String.hpp>

namespace smal
{
    String::String(const char* string, usize length)
        : m_string {string}
        , m_length {length}
    { }

    usize
    String::length() const
    {
        return this->m_length;
    }

    const char*
    String::memory() const
    {
        return this->m_string;
    }

    bool
    String::equals(const String& other, usize count, usize first) const
    {
        char chr1 = 0;
        char chr2 = 0;

        if ( count == (usize) -1 )
            count = this->m_length - first;

        for ( usize i = first; i < count; i++ ) {
            chr1 = this->m_string[i];
            chr2 = other.m_string[i];

            if ( chr1 == 0 || chr1 != chr2 )
                break;
        }

        return chr1 == chr2;
    }

    bool
    String::contains(char byte, usize count, usize first) const
    {
        if ( count == (usize) -1 )
            count = this->m_length - first;

        for ( usize i = first; i < count; i++ ) {
            if ( this->m_string[i] == byte )
                return true;
        }

        return false;
    }
} // namespace smal
