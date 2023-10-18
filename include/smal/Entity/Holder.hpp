#ifndef SMAL_ENTITY_HOLDER_HPP
#define SMAL_ENTITY_HOLDER_HPP

#include <smal/Entity/define.hpp>

namespace smal
{
    template <template <class> class Pool>
    class Holder
    {
    public:
        /**
         * @brief
         *
         * @param origin
         */
        Holder(BaseOrigin* origin);

        /**
         * @brief
         *
         * @tparam Type
         *
         * @return true
         * @return false
         */
        template <class Type>
        bool
        has() const;

        /**
         * @brief
         *
         * @tparam Type
         *
         * @param pool
         *
         * @return true
         * @return false
         */
        template <class Type>
        bool
        give(Pool<Type>* pool);

        /**
         * @brief
         *
         * @tparam Type
         *
         * @return true
         * @return false
         */
        template <class Type>
        bool
        take();

        /**
         * @brief
         *
         * @tparam Type
         *
         * @return Pool<Type>*
         */
        template <class Type>
        Pool<Type>*
        find();

        /**
         * @brief
         *
         * @tparam Type
         *
         * @return const Pool<Type>*
         */
        template <class Type>
        const Pool<Type>*
        find() const;

        /**
         * @brief
         *
         * @tparam Type
         *
         * @param entity
         *
         * @return true
         * @return false
         */
        template <class Type>
        bool
        has(usize entity) const;

        /**
         * @brief
         *
         * @tparam Type
         *
         * @param entity
         * @param attrib
         *
         * @return true
         * @return false
         */
        template <class Type>
        bool
        give(usize entity, const Type& attrib);

        /**
         * @brief
         *
         * @tparam Type
         *
         * @param entity
         * @param attrib
         *
         * @return true
         * @return false
         */
        template <class Type>
        bool
        give(usize entity, Type&& attrib);

        /**
         * @brief
         *
         * @tparam Type
         *
         * @param entity
         *
         * @return true
         * @return false
         */
        template <class Type>
        bool
        take(usize entity);

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
        find(usize entity);

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
        find(usize entity) const;

    private:
        /**
         * @brief
         */
        PagedArray<void*> m_array;
    };
} // namespace smal

#include <smal/Entity/impl/Holder.tpp>

#endif // SMAL_ENTITY_HOLDER_HPP
