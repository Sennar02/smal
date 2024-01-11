#ifndef SMAL_BASE_STRING_HPP
#define SMAL_BASE_STRING_HPP

#include <smal/Base/math.hpp>

#define MA_STRING(str)       \
    {                        \
        str, sizeof(str) - 1 \
    }

namespace ma
{
    class String
    {
    public:
        /**
         *
         */
        String(const char* memory = 0, u32 count = g_max_u32);

        /**
         *
         */
        u32
        count() const;

        /**
         *
         */
        u32
        hash() const;

        /**
         *
         */
        const char*
        memory() const;

        /**
         *
         */
        bool
        equals(const String& that, u32 count, u32 first = 0) const;

        /**
         *
         */
        bool
        equals(const String& that) const;

        /**
         *
         */
        bool
        contains(char byte, u32 count, u32 first = 0) const;

        /**
         *
         */
        bool
        contains(char byte) const;

        /**
         *
         */
        char
        operator[](u32 index);

        /**
         *
         */
        char
        operator[](u32 index) const;

        /**
         *
         */
        bool
        operator==(const String& that) const;

    private:
        /**
         *
         */
        const char* m_memory;

        /**
         *
         */
        u32 m_hash;

        /**
         *
         */
        u32 m_count;
    };
} // namespace ma

#endif // SMAL_BASE_STRING_HPP
