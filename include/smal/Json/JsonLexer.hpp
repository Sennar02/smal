#ifndef SMAL_JSON_JSON_LEXER_HPP
#define SMAL_JSON_JSON_LEXER_HPP

#include <smal/Json/JsonToken.hpp>

namespace ma
{
    class JsonLexer
    {
    private:
        using Type = JsonToken::Type;
        using Flag = JsonToken::Flag;

    public:
        /**
         *
         */
        JsonLexer();

        /**
         *
         */
        JsonLexer(const String& json);

        /**
         *
         */
        bool
        bind(const String& json);

        /**
         *
         */
        JsonToken
        next();

    private:
        /**
         *
         */
        JsonToken
        send(char byte);

        /**
         *
         */
        JsonToken
        string(char quot);

        /**
         *
         */
        JsonToken
        number();

        /**
         *
         */
        JsonToken
        symbol(const String& symbol, JsonToken::Type type);

    private:
        /**
         *
         */
        String m_json;
    };
} // namespace ma

#endif // SMAL_JSON_JSON_LEXER_HPP
