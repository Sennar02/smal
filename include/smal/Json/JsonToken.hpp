#ifndef SMAL_JSON_JSON_TOKEN_HPP
#define SMAL_JSON_JSON_TOKEN_HPP

#include <smal/Json/define.hpp>

namespace ma
{
    class JsonToken
        : public String
    {
    public:
        enum class Type : u32
        {
            String,
            Number,
            Boolean,
            Null,
            ObjOpen,
            ObjClose,
            ArrOpen,
            ArrClose,
            Colon,
            Comma,
            Finish,
            Error,

            SIZE,
        };

        enum Flag : u32
        {
            Flt = 1,
            Neg = 2,
        };

    public:
        /**
         *
         */
        JsonToken();

        /**
         *
         */
        JsonToken(const char* memory, u32 size, Type type, u32 flag = 0);

    public:
        /**
         *
         */
        Type type;

        /**
         *
         */
        u32 flag;
    };
} // namespace ma

#endif // SMAL_JSON_JSON_TOKEN_HPP
