#ifndef SMAL_PARSER_STRING_HPP
#define SMAL_PARSER_STRING_HPP

#include <smal/Parser/define.hpp>

namespace smal
{
    class String
    {
    public:
        /**
         *
         *
         * @param string
         * @param length
         */
        String(const char* string = 0, usize length = 0);

        /**
         *
         *
         * @return
         */
        usize
        length() const;

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
        equals(const String& other, usize count = -1, usize first = 0) const;

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
        contains(char byte, usize count = -1, usize first = 0) const;

    private:
        /**
         *
         */
        const char* m_string;

        /**
         *
         */
        usize m_length;
    };
} // namespace smal

#endif // SMAL_PARSER_STRING_HPP
