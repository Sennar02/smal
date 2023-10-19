#ifndef SMAL_ENTITY_ENTITY_HPP
#define SMAL_ENTITY_ENTITY_HPP

#include <smal/Entity/Status.hpp>

namespace smal
{
    class Entity
    {
    public:
        inline static const usize EMPTY = -1;

    public:
        /**
         *
         */
        Entity();

        /**
         *
         * @return
         */
        usize
        identif() const;

        /**
         *
         * @param status
         *
         * @return True.
         * @return False.
         */
        template <class Status>
        bool
        create(Status& status);

        /**
         *
         * @param status
         *
         * @return True.
         * @return False.
         */
        template <class Status>
        bool
        destroy(Status& status);

        /**
         *
         * @param holder
         *
         * @return True.
         * @return False.
         */
        template <class Type, class Holder>
        bool
        has(Holder& holder) const;

        /**
         *
         * @param holder
         * @param attrib
         *
         * @return True.
         * @return False.
         */
        template <class Type, class Holder>
        bool
        give(Holder& holder, const Type& attrib);

        /**
         *
         * @param holder
         * @param attrib
         *
         * @return True.
         * @return False.
         */
        template <class Type, class Holder>
        bool
        give(Holder& holder, Type&& attrib);

        /**
         *
         * @param holder
         *
         * @return True.
         * @return False.
         */
        template <class Type, class Holder>
        bool
        take(Holder& holder);

        /**
         *
         * @param holder
         *
         * @return
         */
        template <class Type, class Holder>
        Type&
        find(Holder& holder);

        /**
         *
         * @param holder
         *
         * @return
         */
        template <class Type, class Holder>
        const Type&
        find(Holder& holder) const;

    private:
        /**
         *
         */
        usize m_entity;
    };
} // namespace smal

#include <smal/Entity/impl/Entity.tpp>

#endif // SMAL_ENTITY_ENTITY_HPP
