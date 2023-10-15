#include <smal/Memory/Creator.hpp>

namespace smal
{
    template <class Type>
    Creator<Type>::Creator(PoolOrigin& origin)
        : m_origin {origin}
    {
        origin.prepare(SIZE);
    }

    template <class Type>
    Type*
    Creator<Type>::create()
    {
        Part  part = this->m_origin.reserve(SIZE);
        Type* item = (Type*) part.memory();

        if ( part.isNull() == false )
            new (item) Type {};

        return item;
    }

    template <class Type>
    template <class... Args>
    Type*
    Creator<Type>::create(Args&&... args)
    {
        Part  part = this->m_origin.reserve(SIZE);
        Type* item = (Type*) part.memory();

        if ( part.isNull() == false )
            new (item) Type {forw<Args>(args)...};

        return item;
    }

    template <class Type>
    bool
    Creator<Type>::destroy(Type* item)
    {
        Part part = {&this->m_origin, item, SIZE};

        if ( item != 0 ) {
            item->~Type();

            if ( this->m_origin.reclaim(part) )
                return true;
        }

        return false;
    }
} // namespace smal
