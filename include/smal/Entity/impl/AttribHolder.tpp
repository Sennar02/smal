#include <smal/Entity/AttribHolder.hpp>
#include <smal/Entity/AttribCode.hpp>

namespace smal
{
    AttribHolder::AttribHolder(PageAlloc& origin)
        : m_vector {origin}
    { }

    template <class Type>
    bool
    AttribHolder::contains() const
    {
        usize code = AttribCode::of<Type>;

        if ( this->m_vector.size() <= code )
            return false;

        return this->m_vector[code] != 0;
    }

    template <class Type>
    bool
    AttribHolder::insert(SparseTable<Type>* pool)
    {
        usize code = AttribCode::of<Type>;

        if ( this->contains<Type>() == false )
            return this->m_vector.insert(pool, code);

        return false;
    }

    template <class Type>
    bool
    AttribHolder::remove()
    {
        usize code = AttribCode::of<Type>;

        if ( this->contains<Type>() == true )
            return this->m_vector.remove(code);

        return false;
    }

    template <class Type>
    SparseTable<Type>*
    AttribHolder::find()
    {
        usize  code = AttribCode::of<Type>;
        void* addr = this->m_vector[code];

        return (SparseTable<Type>*) addr;
    }

    template <class Type>
    const SparseTable<Type>*
    AttribHolder::find() const
    {
        usize  code = AttribCode::of<Type>;
        void* addr = this->m_vector[code];

        return (SparseTable<Type>*) addr;
    }
} // namespace smal
