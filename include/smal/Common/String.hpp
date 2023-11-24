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
        String(const char* memory = 0, usize size = g_max_usize);

        /**
         *
         */
        usize
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
        equals(const String& other, usize count = g_max_usize, usize first = 0) const;

        /**
         *
        */
        bool
        contains(char byte, usize count = g_max_usize, usize first = 0) const;

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
        usize m_size;
    };
} // namespace ma

#endif // SMAL_COMMON_STRING_HPP
