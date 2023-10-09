#ifndef SMAL_ENTITY_CMP_HOLDER_HPP
#define SMAL_ENTITY_CMP_HOLDER_HPP

#include <smal/Entity/define.hpp>

namespace smal
{
    class CmpHolder
    {
    public:
        /**
         * @brief
         *
         * @param origin
         */
        CmpHolder(PageAlloc& origin);

        /**
         * @brief
         *
         * @tparam Type
         * @return word
         */
        template <class Type>
        word
        number();

        /**
         * @brief
         *
         * @tparam Type
         * @tparam Rest
         *
         * @param entity
         * @param comp
         * @param rest
         *
         * @return true
         * @return false
         */
        template <class Type, class... Rest>
        bool
        give(long entity, const Type& comp, const Rest&... rest);

        /**
         * @brief
         *
         * @tparam Type
         * @tparam Rest
         *
         * @param entity
         * @param comp
         * @param rest
         *
         * @return true
         * @return false
         */
        template <class Type, class... Rest>
        bool
        give(long entity, Type&& comp, Rest&&... rest);

        /**
         * @brief
         *
         * @tparam Type
         * @tparam Rest
         *
         * @param entity
         *
         * @return true
         * @return false
         */
        template <class Type, class... Rest>
        bool
        take(long entity);

        /**
         * @brief
         *
         * @tparam Type
         * @tparam Rest
         *
         * @param entity
         *
         * @return true
         * @return false
         */
        template <class Type, class... Rest>
        bool
        has(long entity);

        /**
         * @brief
         *
         * @tparam Type
         *
         * @param entity
         *
         * @return Type&
         */
        template <class Type>
        Type&
        get(long entity);

        /**
         * @brief
         *
         * @tparam Type
         *
         * @param entity
         *
         * @return const Type&
         */
        template <class Type>
        const Type&
        get(long entity) const;

        /**
         * @brief
         *
         * @return Vector<Address>&
         */
        Vector<Address>&
        pools();

        /**
         * @brief
         *
         * @return const Vector<Address>&
         */
        const Vector<Address>&
        pools() const;

    private:
        /**
         * @brief
         *
         * @tparam Type
         *
         * @return ITable<Type>*
         */
        template <class Type>
        ITable<long, Type>*
        pool();

    private:
        /**
         * @brief
         */
        inline static word g_number = 0;

    private:
        /**
         * @brief
         */
        Vector<Address> m_pools;

        /**
         * @brief
         */
        PageAlloc* m_origin;
    };
} // namespace smal

#include <smal/Entity/impl/CmpHolder.tpp>

#endif // SMAL_ENTITY_CMP_HOLDER_HPP
