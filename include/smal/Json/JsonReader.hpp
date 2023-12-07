#ifndef SMAL_JSON_JSON_READER_HPP
#define SMAL_JSON_JSON_READER_HPP

#include <smal/Json/JsonLexer.hpp>

namespace ma
{
    class JsonReader
    {
    private:
        using Type = JsonToken::Type;
        using Flag = JsonToken::Flag;

    public:
        /**
         *
         */
        JsonReader(u32 depth = 10);

        /**
         *
         */
        JsonReader(JsonClient& client, u32 depth = 10);

        /**
         *
         */
        bool
        bind(JsonClient& client);

        /**
         *
         */
        bool
        read(const String& json);

    private:
        /**
         *
         */
        bool
        send(const JsonToken& token, u32 depth = 0);

        /**
         *
         */
        bool
        string(const JsonToken& token);

        /**
         *
         */
        bool
        number(const JsonToken& token);

        /**
         *
         */
        bool
        boolean(const JsonToken& token);

        /**
         *
         */
        bool
        null(const JsonToken& token);

        /**
         *
         */
        bool
        dict(u32 depth);

        /**
         *
         */
        bool
        list(u32 depth);

    private:
        /**
         *
         */
        JsonLexer m_lexer;

        /**
         *
         */
        JsonClient* m_client;

        /**
         *
         */
        u32 m_depth;
    };
} // namespace ma

#endif // SMAL_JSON_JSON_READER_HPP
