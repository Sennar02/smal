#include <smal/Entity/AttribMng.hpp>

namespace smal
{
    AttribMng::AttribMng(const Vector<void*, PagedArray>& table)
        : m_table {Common::move(table)}
    { }

    template <class Type, class... Rest>
    bool
    AttribMng::give(long entity, const Type& attrib, const Rest&... rest)
    {
        using Pool = SparseMap<Type, PagedArray>;

        auto code = this->type<Type>();
        auto pool = (Pool*) this->m_table[code];

        bool res = pool->insert(entity, attrib);

        if constexpr ( sizeof...(Rest) != 0 )
            return res && this->give<Rest...>(
                              entity, Common::forw<Rest>(rest)...);

        return res;
    }

    template <class Type, class... Rest>
    bool
    AttribMng::give(long entity, Type&& attrib, Rest&&... rest)
    {
        using Pool = SparseMap<Type, PagedArray>;

        auto code = this->type<Type>();
        auto pool = (Pool*) this->m_table[code];

        bool res = pool->insert(entity, Common::move(attrib));

        if constexpr ( sizeof...(Rest) != 0 )
            return res && this->give<Rest...>(
                              entity, Common::forw<Rest>(rest)...);

        return res;
    }

    template <class Type, class... Rest>
    bool
    AttribMng::take(long entity)
    {
        using Pool = SparseMap<Type, PagedArray>;

        auto code = this->type<Type>();
        auto pool = (Pool*) this->m_table[code];

        bool res = pool->remove(entity);

        if constexpr ( sizeof...(Rest) != 0 )
            return res && this->take<Rest...>(entity);

        return res;
    }

    template <class Type>
    Type&
    AttribMng::get(long entity)
    {
        using Pool = SparseMap<Type, PagedArray>;

        auto code = this->type<Type>();
        auto pool = (Pool*) this->m_table[code];

        return pool->access(entity);
    }

    template <class Type>
    const Type&
    AttribMng::get(long entity) const
    {
        using Pool = SparseMap<Type, PagedArray>;

        auto code = this->type<Type>();
        auto pool = (Pool*) this->m_table[code];

        return pool->access(entity);
    }

    template <class Type, class... Rest>
    bool
    AttribMng::has(long entity)
    {
        using Pool = SparseMap<Type, PagedArray>;

        auto code = this->type<Type>();
        auto pool = (Pool*) this->m_table[code];

        bool res = pool->contains(entity);

        if constexpr ( sizeof...(Rest) != 0 )
            return res && this->has<Rest...>(entity);

        return res;
    }

    template <class Type>
    word
    AttribMng::type()
    {
        static word next =
            g_number++;

        return next;
    }
} // namespace smal
