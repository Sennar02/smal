#ifndef SMAL_ENTITY_HOLDER_HPP
#define SMAL_ENTITY_HOLDER_HPP

#include <smal/Entity/define.hpp>

namespace smal
{
    template <template <class> class Pool = SparseMap>
    class Holder
    {
    public:
        /**
         *
         *
         * @param origin
         */
        Holder(BaseOrigin* origin);

        /**
         *
         *
         * @tparam Type
         *
         * @return True.
         * @return False.
         */
        template <class Type>
        bool
        has() const;

        /**
         *
         *
         * @tparam Type
         *
         * @param pool
         *
         * @return True.
         * @return False.
         */
        template <class Type>
        bool
        give(Pool<Type>* pool);

        /**
         *
         *
         * @tparam Type
         *
         * @return True.
         * @return False.
         */
        template <class Type>
        bool
        take();

        /**
         *
         *
         * @tparam Type
         *
         * @return Pool<Type>*
         */
        template <class Type>
        Pool<Type>*
        find();

        /**
         *
         *
         * @tparam Type
         *
         * @return const Pool<Type>*
         */
        template <class Type>
        const Pool<Type>*
        find() const;

        /**
         *
         *
         * @tparam Type
         *
         * @param entity
         *
         * @return True.
         * @return False.
         */
        template <class Type>
        bool
        has(usize entity) const;

        /**
         *
         *
         * @tparam Type
         *
         * @param entity
         * @param attrib
         *
         * @return True.
         * @return False.
         */
        template <class Type>
        bool
        give(usize entity, const Type& attrib);

        /**
         *
         *
         * @tparam Type
         *
         * @param entity
         * @param attrib
         *
         * @return True.
         * @return False.
         */
        template <class Type>
        bool
        give(usize entity, Type&& attrib);

        /**
         *
         *
         * @tparam Type
         *
         * @param entity
         *
         * @return True.
         * @return False.
         */
        template <class Type>
        bool
        take(usize entity);

        /**
         *
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
         *
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
         *
         */
        PagedArray<void*> m_array;
    };
} // namespace smal

#include <smal/Entity/impl/Holder.tpp>

#endif // SMAL_ENTITY_HOLDER_HPP
