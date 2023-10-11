#ifndef SMAL_COMMON_HELPER_HPP
#define SMAL_COMMON_HELPER_HPP

namespace smal
{
    namespace Math
    {
        /**
         * @brief
         *
         * @tparam Type
         *
         * @param a
         * @param b
         *
         * @return Type
         */
        template <class Type>
        Type
        div(Type a, Type b);

        /**
         * @brief
         *
         * @tparam Type
         *
         * @param a
         * @param b
         *
         * @return Type
         */
        template <class Type>
        Type
        mod(Type a, Type b);

        /**
         * @brief
         *
         * @tparam Type
         *
         * @param a
         * @param b
         *
         * @return Type
         */
        template <class Type>
        Type
        floor(Type a, Type b);

        /**
         * @brief
         *
         * @tparam Type
         *
         * @param a
         * @param b
         *
         * @return Type
         */
        template <class Type>
        Type
        ceil(Type a, Type b);

        /**
         * @brief
         *
         * @tparam Type
         *
         * @param a
         * @param b
         *
         * @return Type
         */
        template <class Type>
        Type
        min(Type a, Type b);

        /**
         * @brief
         *
         * @tparam Type
         *
         * @param a
         * @param b
         *
         * @return Type
         */
        template <class Type>
        Type
        max(Type a, Type b);
    } // namespace Math

    namespace impl
    {
        template <class Type>
        struct RemoveRef
        {
            using Result = Type;
        };

        template <class Type>
        struct RemoveRef<Type&>
        {
            using Result = Type;
        };

        template <class Type>
        struct RemoveRef<Type&&>
        {
            using Result = Type;
        };
    } // namespace impl

    template <class Type>
    using RemoveRef = typename impl::RemoveRef<Type>::Result;

    /**
         * @brief
         *
         * @tparam Type
         *
         * @param value
         *
         * @return RemoveRef<Type>&&
         */
    template <class Type>
    RemoveRef<Type>&&
    move(Type&& value);

    /**
         * @brief
         *
         * @tparam Type
         *
         * @param value
         *
         * @return Type&&
         */
    template <class Type>
    Type&&
    forw(RemoveRef<Type>& value);

    /**
         * @brief
         *
         * @tparam Type
         *
         * @param value
         *
         * @return Type&&
         */
    template <class Type>
    Type&&
    forw(RemoveRef<Type>&& value);

    /**
         * @brief
         *
         * @tparam Type
         *
         * @param value
         * @param other
         *
         * @return Type&
         */
    template <class Type>
    Type&
    swap(Type& value, Type& other);

    /**
         * @brief
         *
         * @tparam Type
         *
         * @param value
         * @param other
         *
         * @return Type
         */
    template <class Type>
    Type
    exch(Type& value, Type&& other);

    /**
         * @brief
         *
         * @tparam Type
         *
         * @param value
         *
         * @return Type&
         */
    template <class Type>
    Type&
    create(Type& value);

    /**
         * @brief
         *
         * @tparam Type
         * @tparam Args
         *
         * @param value
         * @param args
         *
         * @return Type&
         */
    template <class Type, class... Args>
    Type&
    create(Type& value, Args&&... args);

    /**
         * @brief
         *
         * @tparam Type

         * @param value

         * @return Type&
         */
    template <class Type>
    Type&
    destroy(Type& value);
} // namespace smal

#include <smal/Common/impl/helper.tpp>

#endif // SMAL_COMMON_HELPER_HPP
