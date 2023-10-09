#include <smal/Entity/CmpHolder.hpp>

namespace smal
{
    using namespace Common;

    CmpHolder::CmpHolder(PageAlloc& origin)
        : m_pools {origin}
        , m_origin {&origin}
    { }

    template <class Type>
    ITable<long, Type>*
    CmpHolder::pool()
    {
        auto index = this->number<Type>();
        auto pool  = this->m_pools[index];

        return (ITable<long, Type>*) pool;
    }

    template <class Type, class... Rest>
    bool
    CmpHolder::give(long entity, const Type& comp, const Rest&... rest)
    {
        auto pool = this->pool<Type>();
        bool oper = true;

        if ( pool != 0 ) {
            oper = pool->insert(entity, comp);

            if constexpr ( sizeof...(Rest) != 0 )
                oper &= this->give<Rest...>(entity, rest...);
        }

        return oper;
    }

    template <class Type, class... Rest>
    bool
    CmpHolder::give(long entity, Type&& comp, Rest&&... rest)
    {
        auto pool = this->pool<Type>();
        bool oper = true;

        if ( pool != 0 ) {
            oper = pool->insert(entity, comp);

            if constexpr ( sizeof...(Rest) != 0 )
                oper &= this->give<Rest...>(entity, forw<Rest>(rest)...);
        }

        return oper;
    }

    template <class Type, class... Rest>
    bool
    CmpHolder::take(long entity)
    {
        auto pool = this->pool<Type>();
        bool oper = true;

        if ( pool != 0 ) {
            oper = pool->remove(entity);

            if constexpr ( sizeof...(Rest) != 0 )
                oper &= this->take<Rest...>(entity);
        }

        return oper;
    }

    template <class Type, class... Rest>
    bool
    CmpHolder::has(long entity)
    {
        auto pool = this->pool<Type>();
        bool oper = true;

        if ( pool != 0 ) {
            oper = pool->contains(entity);

            if constexpr ( sizeof...(Rest) != 0 )
                oper &= this->take<Rest...>(entity);
        }

        return oper;
    }

    template <class Type>
    Type&
    CmpHolder::get(long entity)
    {
        auto pool = this->pool<Type>();

        return pool->operator[](entity);
    }

    template <class Type>
    const Type&
    CmpHolder::get(long entity) const
    {
        auto pool = this->pool<Type>();

        return pool->operator[](entity);
    }

    Vector<Address>&
    CmpHolder::pools()
    {
        return this->m_pools;
    }

    const Vector<Address>&
    CmpHolder::pools() const
    {
        return this->m_pools;
    }

    template <class Type>
    word
    CmpHolder::number()
    {
        static word next =
            g_number++;

        return next;
    }
} // namespace smal
