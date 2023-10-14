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
         * @param buffer
         */
        Attributes(PageAlloc& origin, ArenaAlloc& buffer);

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
        give(usize entity, const Type& comp, const Rest&... rest);

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
        give(usize entity, Type&& comp, Rest&&... rest);

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
        take(usize entity);

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
        has(usize entity) const;

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
        get(usize entity);

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
        get(usize entity) const;

        /**
         * @brief
         *
         * @tparam Type
         * @tparam Rest
         *
         * @return true
         * @return false
         */
        template <class Type, class... Rest>
        bool
        has() const;

        /**
         * @brief
         *
         * @tparam Type
         *
         * @return SparseTable<Type>&
         */
        template <class Type>
        SparseTable<Type>&
        get();

        /**
         * @brief
         *
         * @tparam Type
         *
         * @return const SparseTable<Type>&
         */
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

        /**
         * @brief
         */
        ArenaAlloc* m_buffer;
    };
} // namespace smal

#include <smal/Entity/impl/Attributes.tpp>

#endif // SMAL_ENTITY_ATTRIBUTES_HPP
