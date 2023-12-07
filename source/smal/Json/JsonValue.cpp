#include <smal/Json/JsonValue.hpp>

namespace ma
{
    JsonValue::JsonValue()
        : m_memory {0}
        , m_size {0}
        , m_type {Type::Null}
    { }

    JsonValue::JsonValue(const String& value)
        : m_memory {value.memory()}
        , m_size {value.size()}
        , m_type {Type::String}
    { }

    JsonValue::JsonValue(const char* memory, u32 size)
        : JsonValue(String {memory, size})
    { }

    JsonValue::JsonValue(u32 value)
        : m_memory {*(char**) &value}
        , m_size {sizeof(u32)}
        , m_type {Type::Unsig}
    { }

    JsonValue::JsonValue(i32 value)
        : m_memory {*(char**) &value}
        , m_size {sizeof(i32)}
        , m_type {Type::Negat}
    { }

    JsonValue::JsonValue(f32 value)
        : m_memory {*(char**) &value}
        , m_size {sizeof(f32)}
        , m_type {Type::Float}
    { }

    JsonValue::JsonValue(bool value)
        : m_memory {*(char**) &value}
        , m_size {sizeof(bool)}
        , m_type {Type::Boolean}
    { }

    JsonValue::JsonValue(JsonObject& object)
        : m_memory {(char*) &object}
        , m_size {sizeof(char*)}
        , m_type {Type::Object}
    { }

    JsonValue::JsonValue(JsonArray& array)
        : m_memory {(char*) &array}
        , m_size {sizeof(char*)}
        , m_type {Type::Array}
    { }

    const char*
    JsonValue::memory() const
    {
        return m_memory;
    }

    u32
    JsonValue::size() const
    {
        return m_size;
    }

    JsonValue::Type
    JsonValue::type() const
    {
        return m_type;
    }

    bool
    JsonValue::isString() const
    {
        return m_type == Type::String;
    }

    bool
    JsonValue::isNumber() const
    {
        return m_type == Type::Unsig ||
               m_type == Type::Negat ||
               m_type == Type::Float;
    }

    bool
    JsonValue::isUnsig() const
    {
        return m_type == Type::Unsig;
    }

    bool
    JsonValue::isNegat() const
    {
        return m_type == Type::Negat;
    }

    bool
    JsonValue::isFloat() const
    {
        return m_type == Type::Float;
    }

    bool
    JsonValue::isBoolean() const
    {
        return m_type == Type::Boolean;
    }

    bool
    JsonValue::isNull() const
    {
        return m_type == Type::Null;
    }

    bool
    JsonValue::isObject() const
    {
        return m_type == Type::Object;
    }

    bool
    JsonValue::isArray() const
    {
        return m_type == Type::Array;
    }

    String
    JsonValue::toString() const
    {
        if ( m_type == Type::String )
            return String {(const char*) m_memory, m_size};

        return {};
    }

    u32
    JsonValue::toUnsig() const
    {
        if ( m_type == Type::Unsig ||
             m_type == Type::Negat )
            return *(u32*) &m_memory;

        return 0;
    }

    i32
    JsonValue::toNegat() const
    {
        if ( m_type == Type::Unsig ||
             m_type == Type::Negat )
            return *(i32*) &m_memory;

        return 0;
    }

    f32
    JsonValue::toFloat() const
    {
        if ( m_type == Type::Unsig ||
             m_type == Type::Negat ||
             m_type == Type::Float )
            return *(f32*) &m_memory;

        return 0;
    }

    bool
    JsonValue::toBoolean() const
    {
        if ( m_type == Type::Boolean )
            return *(bool*) &m_memory;

        return false;
    }

    JsonObject&
    JsonValue::toObject()
    {
        if ( m_type == Type::Object )
            return *(JsonObject*) m_memory;

        return *(JsonObject*) 0;
    }

    JsonArray&
    JsonValue::toArray()
    {
        if ( m_type == Type::Array )
            return *(JsonArray*) m_memory;

        return *(JsonArray*) 0;
    }
} // namespace ma
