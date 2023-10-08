#ifndef SMAL_STRUCT_ITABLE_HPP
#define SMAL_STRUCT_ITABLE_HPP

#include <smal/Struct/define.hpp>

namespace smal
{
    template <class Key, class Value>
    class ITable
    {
    public:
        /**
         * @brief
         */
        virtual ~ITable() = default;

        /**
         * @brief
         *
         * @param key
         *
         * @return true
         * @return false
         */
        virtual bool
        contains(const Key& key) const = 0;

        /**
         * @brief
         *
         * @param key
         * @param value
         *
         * @return true
         * @return false
         */
        virtual bool
        insert(const Key& key, const Value& value) = 0;

        /**
         * @brief
         *
         * @param key
         * @param value
         *
         * @return true
         * @return false
         */
        virtual bool
        insert(const Key& key, Value&& value) = 0;

        /**
         * @brief
         *
         * @param key
         *
         * @return true
         * @return false
         */
        virtual bool
        remove(const Key& key) = 0;

        /**
         * @brief
         *
         * @param key
         *
         * @return Value&
         */
        virtual Value&
        operator[](const Key& key) = 0;

        /**
         * @brief
         *
         * @param key
         *
         * @return const Value&
         */
        virtual const Value&
        operator[](const Key& key) const = 0;
    };
} // namespace smal

#endif // SMAL_STRUCT_ITABLE_HPP
