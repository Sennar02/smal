#include <smal/Entity/Attributes.hpp>

namespace smal
{
    Attributes::Attributes(PageAlloc& origin, ArenaAlloc& buffer)
        : m_holder {origin}
        , m_origin {&origin}
        , m_buffer {&buffer}
    { }

    template <class Type, class... Rest>
    bool
    Attributes::give(long entity, const Type& comp, const Rest&... rest)
    {
        if ( this->m_holder.template contains<Type>() == false )
            this->template provide<Type>();

        auto pool = this->m_holder.template find<Type>();
        bool oper = false;

        if ( pool != 0 ) {
            oper = pool->insert(entity, comp);

            if constexpr ( sizeof...(Rest) != 0 )
                oper &= this->give(entity, rest...);
        }

        return oper;
    }

    template <class Type, class... Rest>
    bool
    Attributes::give(long entity, Type&& comp, Rest&&... rest)
    {
        if ( this->m_holder.template contains<Type>() == false )
            this->template provide<Type>();

        auto pool = this->m_holder.template find<Type>();
        bool oper = false;

        if ( pool != 0 ) {
            oper = pool->insert(entity, move(comp));

            if constexpr ( sizeof...(Rest) != 0 )
                oper &= this->give(entity, forw<Rest>(rest)...);
        }

        return oper;
    }

    template <class Type, class... Rest>
    bool
    Attributes::take(long entity)
    {
        if ( this->m_holder.template contains<Type>() == false )
            return false;

        auto pool = this->m_holder.template find<Type>();
        bool oper = false;

        if ( pool != 0 ) {
            oper = pool->remove(entity);

            if constexpr ( sizeof...(Rest) != 0 )
                oper &= this->take<Rest...>(entity);
        }

        return oper;
    }

    template <class Type, class... Rest>
    bool
    Attributes::has(long entity) const
    {
        if ( this->m_holder.template contains<Type>() == false )
            return false;

        auto pool = this->m_holder.template find<Type>();
        bool oper = false;

        if ( pool != 0 ) {
            oper = pool->contains(entity);

            if constexpr ( sizeof...(Rest) != 0 )
                oper &= this->has<Rest...>(entity);
        }

        return oper;
    }

    template <class Type>
    Type&
    Attributes::get(long entity)
    {
        auto pool = this->m_holder.template find<Type>();

        return pool->operator[](entity);
    }

    template <class Type>
    const Type&
    Attributes::get(long entity) const
    {
        auto pool = this->m_holder.template find<Type>();

        return pool->operator[](entity);
    }

    template <class Type, class... Rest>
    bool
    Attributes::has() const
    {
        bool oper = false;

        if ( this->m_holder.template contains<Type>() ) {
            oper = true;

            if constexpr ( sizeof...(Rest) != 0 )
                oper &= this->has<Rest...>();
        }

        return oper;
    }

    template <class Type>
    SparseTable<Type>&
    Attributes::get()
    {
        return *this->m_holder.template find<Type>();
    }

    template <class Type>
    const SparseTable<Type>&
    Attributes::get() const
    {
        return *this->m_holder.template find<Type>();
    }

    AttribHolder&
    Attributes::holder()
    {
        return this->m_holder;
    }

    template <class Type>
    void
    Attributes::provide()
    {
        long size = sizeof(SparseTable<Type>);
        Part part = this->m_buffer->reserve(size);

        auto* table = (SparseTable<Type>*) part.memory();

        create(*table,
            *this->m_origin,
            *this->m_origin,
            *this->m_origin);

        this->m_holder.template insert<Type>(table);
    }
} // namespace smal
