#ifndef SMAL_ENTITY_ATTRIBUTES_HPP
#define SMAL_ENTITY_ATTRIBUTES_HPP

#include <smal/Entity/AttribHolder.hpp>

namespace smal
{
    class Attributes
    {
    public:
        /**
         * @brief
         *
         * @param origin
         */
        Attributes(PageAlloc& origin);

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
        has(long entity) const;

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

        template <class Type, class... Rest>
        bool
        has() const;

        template <class Type>
        SparseTable<Type>&
        get();

        template <class Type>
        const SparseTable<Type>&
        get() const;

        /**
         * @brief
         *
         * @return AttribHolder&
         */
        AttribHolder&
        holder();

    private:
        /**
         * @brief
         *
         * @tparam Type
         */
        template <class Type>
        void
        provide();

    private:
        /**
         * @brief
         */
        AttribHolder m_holder;

        /**
         * @brief
         */
        PageAlloc* m_origin;
    };
} // namespace smal

#include <smal/Entity/impl/Attributes.tpp>

#endif // SMAL_ENTITY_ATTRIBUTES_HPP
