#include <smal/Entity/Entity.hpp>

namespace smal
{
    Entity::Entity()
        : m_entity {(usize) &EMPTY}
    { }

    usize
    Entity::identif() const
    {
        return this->m_entity;
    }

    template <class Status>
    bool
    Entity::create(Status& status)
    {
        if ( this->m_entity == (usize) &EMPTY )
            this->m_entity = status.create();

        return this->m_entity != (usize) &EMPTY;
    }

    template <class Status>
    bool
    Entity::destroy(Status& status)
    {
        if ( this->m_entity != (usize) &EMPTY ) {
            status.destroy(this->m_entity);

            this->m_entity = (usize) &EMPTY;
        }

        return this->m_entity == (usize) &EMPTY;
    }

    template <class Type, class Holder>
    bool
    Entity::has(Holder& holder) const
    {
        return holder.template has<Type>(this->m_entity);
    }

    template <class Type, class Holder>
    bool
    Entity::give(Holder& holder, const Type& attrib)
    {
        return holder.template give<Type>(this->m_entity, attrib);
    }

    template <class Type, class Holder>
    bool
    Entity::give(Holder& holder, Type&& attrib)
    {
        return holder.template give<Type>(this->m_entity, move(attrib));
    }

    template <class Type, class Holder>
    bool
    Entity::take(Holder& holder)
    {
        return holder.template take<Type>(this->m_entity);
    }

    template <class Type, class Holder>
    Type&
    Entity::find(Holder& holder)
    {
        return holder.template find<Type>(this->m_entity);
    }

    template <class Type, class Holder>
    const Type&
    Entity::find(Holder& holder) const
    {
        return holder.template find<Type>(this->m_entity);
    }
} // namespace smal
