#ifndef SMAL_COMMON_STRING_HPP
#define SMAL_COMMON_STRING_HPP

#include <smal/Common/define.hpp>

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
        equals(const String& other, u32 count = g_max_u32, u32 first = 0) const;

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
        operator==(const String& other) const;

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

#endif // SMAL_COMMON_STRING_HPP
