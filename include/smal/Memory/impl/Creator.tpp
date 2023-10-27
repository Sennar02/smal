#include <smal/Memory/Creator.hpp>

namespace ma
{
    template <class Type>
    Type*
    Creator::create()
    {
        static usize size = sizeof(Type);

        Page  part = this->m_origin->reserve(size);
        Type* item = (Type*) part.memory();

        if ( part.isNull() == false )
            new (item) Type {};

        return item;
    }

    template <class Type, class... Args>
    Type*
    Creator::create(Args&&... args)
    {
        static usize size = sizeof(Type);

        Page  part = this->m_origin->reserve(size);
        Type* item = (Type*) part.memory();

        if ( part.isNull() == false )
            new (item) Type {forw<Args>(args)...};

        return item;
    }

    template <class Type>
    bool
    Creator::destroy(Type* item)
    {
        static usize size = sizeof(Type);

        Page part = {this->m_origin, item, size};

        if ( item != 0 ) {
            item->~Type();

            if ( this->m_origin->reclaim(part) )
                return true;
        }

        return false;
    }
} // namespace ma
