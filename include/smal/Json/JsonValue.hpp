#ifndef SMAL_JSON_JSON_VALUE_HPP
#define SMAL_JSON_JSON_VALUE_HPP

#include <smal/Json/define.hpp>

namespace ma
{
    using JsonObject = HashTable<String, JsonValue>;
    using JsonArray  = ArrayList<JsonValue>;

    class JsonValue
    {
    public:
        enum class Type
        {
            String,
            Unsig,
            Negat,
            Float,
            Boolean,
            Null,
            Object,
            Array,

            SIZE,
        };

    public:
        /**
         *
         */
        JsonValue();

        /**
         *
         */
        JsonValue(const String& value);

        /**
         *
         */
        JsonValue(const char* memory, u32 size = g_max_u32);

        /**
         *
         */
        JsonValue(u32 value);

        /**
         *
         */
        JsonValue(i32 value);

        /**
         *
         */
        JsonValue(f32 value);

        /**
         *
         */
        JsonValue(bool value);

        /**
         *
         */
        JsonValue(JsonObject& object);

        /**
         *
         */
        JsonValue(JsonArray& array);

        /**
         *
         */
        virtual ~JsonValue() = default;

        /**
         *
         */
        const char*
        memory() const;

        /**
         *
         */
        u32
        size() const;

        /**
         *
         */
        Type
        type() const;

        /**
         *
         */
        bool
        isString() const;

        /**
         *
         */
        bool
        isNumber() const;

        /**
         *
         */
        bool
        isUnsig() const;

        /**
         *
         */
        bool
        isNegat() const;

        /**
         *
         */
        bool
        isFloat() const;

        /**
         *
         */
        bool
        isBoolean() const;

        /**
         *
         */
        bool
        isNull() const;

        /**
         *
         */
        bool
        isObject() const;

        /**
         *
         */
        bool
        isArray() const;

        /**
         *
         */
        String
        toString() const;

        /**
         *
         */
        u32
        toUnsig() const;

        /**
         *
         */
        i32
        toNegat() const;

        /**
         *
         */
        f32
        toFloat() const;

        /**
         *
         */
        bool
        toBoolean() const;

        /**
         *
         */
        JsonObject&
        toObject();

        /**
         *
         */
        JsonArray&
        toArray();

    private:
        /**
         *
         */
        const char* m_memory;

        /**
         *
         */
        u32 m_size;

        /**
         *
         */
        Type m_type;
    };
} // namespace ma

#endif // SMAL_JSON_JSON_VALUE_HPP
