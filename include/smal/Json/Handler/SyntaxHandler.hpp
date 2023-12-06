#ifndef SMAL_JSON_HANDLER_SYNTAX_HANDLER_HPP
#define SMAL_JSON_HANDLER_SYNTAX_HANDLER_HPP

#include <smal/Json/define.hpp>

namespace ma
{
    class SyntaxHandler
        : public BaseHandler
    {
    public:
        /**
         *
         */
        virtual bool
        string(const String value)
        {
            return true;
        }

        /**
         *
         */
        virtual bool
        number(u32 value)
        {
            return true;
        }

        /**
         *
         */
        virtual bool
        number(i32 value)
        {
            return true;
        }

        /**
         *
         */
        virtual bool
        number(f32 value)
        {
            return true;
        }

        /**
         *
         */
        virtual bool
        boolean(bool value)
        {
            return true;
        }

        /**
         *
         */
        virtual bool
        null()
        {
            return true;
        }

        /**
         *
         */
        virtual bool
        listEnter(u32 depth)
        {
            return true;
        }

        /**
         *
         */
        virtual bool
        listLeave(u32 depth, u32 count)
        {
            return true;
        }

        /**
         *
         */
        virtual bool
        dictEnter(u32 depth)
        {
            return true;
        }

        /**
         *
         */
        virtual bool
        dictProp(const String prop)
        {
            return true;
        }

        /**
         *
         */
        virtual bool
        dictLeave(u32 depth, u32 count)
        {
            return true;
        }
    };
} // namespace ma

#endif // SMAL_JSON_HANDLER_SYNTAX_HANDLER_HPP
