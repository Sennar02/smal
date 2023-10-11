#ifndef SMAL_ENTITY_ATTRIB_HOLDER_HPP
#define SMAL_ENTITY_ATTRIB_HOLDER_HPP

#include <smal/Entity/define.hpp>

namespace smal
{
    template <template <class> class Table>
    class AttribHolder
    {
    public:
        AttribHolder(PageAlloc& origin);

        template <class Type>
        bool
        contains() const;

        template <class Type>
        bool
        insert(Table<Type>* pool);

        template <class Type>
        bool
        remove();

        template <class Type>
        Table<Type>&
        find();

        template <class Type>
        const Table<Type>&
        find() const;

    private:
        Vector<void*> m_vector;
    };
} // namespace smal

#include <smal/Entity/impl/AttribHolder.tpp>

#endif // SMAL_ENTITY_ATTRIB_HOLDER_HPP
