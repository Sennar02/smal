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
         *
         * @param memory
         * @param size
         */
        String(const char* memory = 0, usize size = g_max_usize);

        /**
         *
         *
         * @return
         */
        usize
        size() const;

        /**
         *
         *
         * @return
         */
        const char*
        memory() const;

        /**
         *
         *
         * @param other
         * @param count
         * @param first
         *
         * @return True.
         * @return False.
         */
        bool
        equals(const String& other, usize count = g_max_usize, usize first = 0) const;

        /**
         *
         *
         * @param byte
         * @param count
         * @param first
         *
         * @return True.
         * @return False.
        */
        bool
        contains(char byte, usize count = g_max_usize, usize first = 0) const;

        /**
         *
         *
         * @param other
         *
         * @return True.
         * @return False.
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
