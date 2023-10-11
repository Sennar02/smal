#include <smal/Entity/AttribHolder.hpp>
#include <smal/Entity/AttribCode.hpp>

namespace smal
{
    template <template <class> class Table>
    AttribHolder<Table>::AttribHolder(PageAlloc& origin)
        : m_vector {origin}
    { }

    template <template <class> class Table>
    template <class Type>
    bool
    AttribHolder<Table>::contains() const
    {
        long code = AttribCode::of<Type>;

        if ( this->m_vector.size() <= code )
            return false;

        return this->m_vector[code] != 0;
    }

    template <template <class> class Table>
    template <class Type>
    bool
    AttribHolder<Table>::insert(Table<Type>* pool)
    {
        long code = AttribCode::of<Type>;

        if ( this->contains<Type>() == false )
            return this->m_vector.insert(pool, code);

        return false;
    }

    template <template <class> class Table>
    template <class Type>
    bool
    AttribHolder<Table>::remove()
    {
        long code = AttribCode::of<Type>;

        if ( this->contains<Type>() == true )
            return this->m_vector.remove(code);

        return false;
    }

    template <template <class> class Table>
    template <class Type>
    Table<Type>&
    AttribHolder<Table>::find()
    {
        long  code = AttribCode::of<Type>;
        void* addr = this->m_vector[code];

        return *(Table<Type>*) addr;
    }

    template <template <class> class Table>
    template <class Type>
    const Table<Type>&
    AttribHolder<Table>::find() const
    {
        long  code = AttribCode::of<Type>;
        void* addr = this->m_vector[code];

        return *(Table<Type>*) addr;
    }
} // namespace smal
