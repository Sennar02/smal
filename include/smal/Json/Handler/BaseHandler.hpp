#ifndef SMAL_JSON_HANDLER_BASE_HANDLER_HPP
#define SMAL_JSON_HANDLER_BASE_HANDLER_HPP

#include <smal/Json/define.hpp>

namespace ma
{
    class BaseHandler
    {
    public:
        /**
         *
         */
        virtual ~BaseHandler() = default;

        /**
         *
         */
        virtual bool
        string(const String value) = 0;

        /**
         *
         */
        virtual bool
        number(u32 value) = 0;

        /**
         *
         */
        virtual bool
        number(i32 value) = 0;

        /**
         *
         */
        virtual bool
        number(f32 value) = 0;

        /**
         *
         */
        virtual bool
        boolean(bool value) = 0;

        /**
         *
         */
        virtual bool
        null() = 0;

        /**
         *
         */
        virtual bool
        listEnter(u32 depth) = 0;

        /**
         *
         */
        virtual bool
        listLeave(u32 depth, u32 count) = 0;

        /**
         *
         */
        virtual bool
        dictEnter(u32 depth) = 0;

        /**
         *
         */
        virtual bool
        dictProp(const String prop) = 0;

        /**
         *
         */
        virtual bool
        dictLeave(u32 depth, u32 count) = 0;
    };
} // namespace ma

#endif // SMAL_JSON_HANDLER_BASE_HANDLER_HPP
