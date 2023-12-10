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
        template <class User>
        bool
        read(User& user, const String& json);

    private:
        /**
         *
         */
        template <class User>
        bool
        deduce(User& user, const JsonToken& token, u32 depth = 0);

        /**
         *
         */
        template <class User>
        bool
        string(User& user, const JsonToken& token);

        /**
         *
         */
        template <class User>
        bool
        number(User& user, const JsonToken& token);

        /**
         *
         */
        template <class User>
        bool
        number(User& user, u32 item);

        /**
         *
         */
        template <class User>
        bool
        number(User& user, i32 item);

        /**
         *
         */
        template <class User>
        bool
        number(User& user, f32 item);

        /**
         *
         */
        template <class User>
        bool
        boolean(User& user, const JsonToken& token);

        /**
         *
         */
        template <class User>
        bool
        null(User& user, const JsonToken& token);

        /**
         *
         */
        template <class User>
        bool
        object(User& user, u32 depth);

        /**
         *
         */
        template <class User>
        bool
        array(User& user, u32 depth);

    private:
        /**
         *
         */
        JsonLexer m_lexer;

        /**
         *
         */
        u32 m_depth;
    };
} // namespace ma

#include <smal/Json/impl/JsonReader.tpp>

#endif // SMAL_JSON_JSON_READER_HPP
