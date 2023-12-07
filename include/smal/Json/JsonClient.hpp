#ifndef SMAL_JSON_HANDLER_BASE_HANDLER_HPP
#define SMAL_JSON_HANDLER_BASE_HANDLER_HPP

#include <smal/Json/define.hpp>

namespace ma
{
    class JsonClient
    {
    public:
        /**
         *
         */
        virtual ~JsonClient() = default;

        /**
         *
         */
        virtual bool
        string(const String value);

        /**
         *
         */
        virtual bool
        number(u32 value);

        /**
         *
         */
        virtual bool
        number(i32 value);

        /**
         *
         */
        virtual bool
        number(f32 value);

        /**
         *
         */
        virtual bool
        boolean(bool value);

        /**
         *
         */
        virtual bool
        null();

        /**
         *
         */
        virtual bool
        listEnter(u32 depth);

        /**
         *
         */
        virtual bool
        listLeave(u32 depth, u32 count);

        /**
         *
         */
        virtual bool
        dictEnter(u32 depth);

        /**
         *
         */
        virtual bool
        dictProp(const String prop);

        /**
         *
         */
        virtual bool
        dictLeave(u32 depth, u32 count);
    };
} // namespace ma

#endif // SMAL_JSON_HANDLER_BASE_HANDLER_HPP
