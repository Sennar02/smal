#ifndef SMAL_BASE_STRING_HPP
#define SMAL_BASE_STRING_HPP

#include <smal/Base/define.hpp>

namespace ma
{
    class String
    {
    public:
        /**
         *
         */
        String(const char* memory = 0, u32 size = g_max_u32);

        /**
         *
         */
        u32
        size() const;

        /**
         *
         */
        const char*
        memory() const;

        /**
         *
         */
        bool
        equals(const String& that, u32 count = g_max_u32, u32 first = 0) const;

        /**
         *
        */
        bool
        contains(char byte, u32 count = g_max_u32, u32 first = 0) const;

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
        u32 m_size;
    };
} // namespace ma

#endif // SMAL_BASE_STRING_HPP
