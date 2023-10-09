#include <smal/Memory/Buffer.hpp>

namespace smal
{
    using namespace Common;

    template <long Len>
    template <class Type>
    Buffer<Len>::Buffer(const Type& value)
        : m_memory {{0}}
    {
        create(*(Type*) this->m_memory,
            value);
    }

    template <long Len>
    template <class Type>
    Buffer<Len>::Buffer(Type&& value)
        : m_memory {{0}}
    {
        create(*(Type*) this->m_memory,
            move(value));
    }

    template <long Len>
    template <class Type>
    Type*
    Buffer<Len>::memory()
    {
        return (Type*) this->m_memory;
    }

    template <long Len>
    template <class Type>
    const Type*
    Buffer<Len>::memory() const
    {
        return (Type*) this->m_memory;
    }
} // namespace smal
