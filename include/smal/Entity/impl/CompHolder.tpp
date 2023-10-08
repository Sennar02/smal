#include <smal/Entity/CompHolder.hpp>

namespace smal
{
    using namespace Common;

    CompHolder::CompHolder(PageAlloc& origin)
        : m_pools {origin}
        , m_origin {&origin}
    { }

    template <class Type>
    ITable<long, Type>*
    CompHolder::pool()
    {
        auto index = this->number<Type>();
        auto pool  = this->m_pools[index];

        return (ITable<long, Type>*) pool;
    }

    template <class Type, class... Rest>
    bool
    CompHolder::give(long entity, const Type& comp, const Rest&... rest)
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
    CompHolder::give(long entity, Type&& comp, Rest&&... rest)
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
    CompHolder::take(long entity)
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
    CompHolder::has(long entity)
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
    CompHolder::get(long entity)
    {
        auto pool = this->pool<Type>();

        return pool->operator[](entity);
    }

    template <class Type>
    const Type&
    CompHolder::get(long entity) const
    {
        auto pool = this->pool<Type>();

        return pool->operator[](entity);
    }

    Vector<Address>&
    CompHolder::pools()
    {
        return this->m_pools;
    }

    const Vector<Address>&
    CompHolder::pools() const
    {
        return this->m_pools;
    }

    template <class Type>
    word
    CompHolder::number()
    {
        static word next =
            g_number++;

        return next;
    }
} // namespace smal
