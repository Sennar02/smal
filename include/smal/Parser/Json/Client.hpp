#ifndef SMAL_PARSER_JSON_CLIENT_HPP
#define SMAL_PARSER_JSON_CLIENT_HPP

#include <smal/Parser/define.hpp>

namespace ma::Json
{
    class Client
    {
    public:
        /**
         *
         */
        virtual ~Client();

        /**
         *
         *
         * @param string
         * @param length
         *
         * @return True.
         * @return False.
         */
        virtual bool
        string(const char* string, usize length);

        /**
         *
         *
         * @param value
         *
         * @return True.
         * @return False.
         */
        virtual bool
        number(usize value);

        /**
         *
         *
         * @param value
         *
         * @return True.
         * @return False.
         */
        virtual bool
        number(isize value);

        /**
         *
         *
         * @param value
         *
         * @return True.
         * @return False.
         */
        virtual bool
        number(f64 value);

        /**
         *
         *
         * @param value
         *
         * @return True.
         * @return False.
         */
        virtual bool
        boolean(bool value);

        /**
         *
         *
         * @return True.
         * @return False.
         */
        virtual bool
        null();

        /**
         *
         *
         * @param string
         * @param length
         *
         * @return True.
         * @return False.
         */
        virtual bool
        name(const char* string, usize length);

        /**
         *
         *
         * @param depth
         *
         * @return True.
         * @return False.
         */
        virtual bool
        array_start(usize depth);

        /**
         *
         *
         * @param depth
         * @param count
         *
         * @return True.
         * @return False.
         */
        virtual bool
        array_stop(usize depth, usize count);

        /**
         *
         *
         * @param depth
         *
         * @return True.
         * @return False.
         */
        virtual bool
        object_start(usize depth);

        /**
         *
         *
         * @param depth
         * @param count
         *
         * @return True.
         * @return False.
         */
        virtual bool
        object_stop(usize depth, usize count);
    };
} // namespace ma::Json

#endif // SMAL_PARSER_JSON_CLIENT_HPP
