#ifndef SMAL_ENTITY_ATTRIB_MNGR_HPP
#define SMAL_ENTITY_ATTRIB_MNGR_HPP

#include <smal/Entity/define.hpp>

namespace smal
{
    class AttribMng
    {
    public:
        AttribMng(const Vector<void*, PagedArray>& table);

        template <class Type, class... Rest>
        bool
        give(long entity, const Type& attrib, const Rest&... rest);

        template <class Type, class... Rest>
        bool
        give(long entity, Type&& attrib, Rest&&... rest);

        template <class Type, class... Rest>
        bool
        take(long entity);

        template <class Type, class... Rest>
        bool
        has(long entity);

        template <class Type>
        Type&
        get(long entity);

        template <class Type>
        const Type&
        get(long entity) const;

    private:
        template <class Type>
        word
        type();

    private:
        inline static word g_number = 0;

    private:
        Vector<void*, PagedArray> m_table;
    };
} // namespace smal

#include <smal/Entity/impl/AttribMng.tpp>

#endif // SMAL_ENTITY_ATTRIB_MNGR_HPP
