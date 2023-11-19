#ifndef SMAL_STRUCT_DATA_HASH_MAP_HPP
#define SMAL_STRUCT_DATA_HASH_MAP_HPP

#include <smal/Struct/define.hpp>

namespace ma
{
    template <class Iden, class Type, template <class> class Array = PagedArray>
    class HashMap
    {
    public:
        HashMap();

        HashMap(BaseOrigin* origin, usize size = 0);

        virtual ~HashMap() = default;

        usize
        size() const;

        usize
        count() const;

        f32
        load() const;

        bool
        is_empty() const;

        bool
        is_full() const;

        template <class Func>
        bool
        contains(const Iden& iden, Func comp) const;

        bool
        contains(const Iden& iden) const;

        template <class Func>
        void
        for_each(Func oper) const;

        template <class Func>
        bool
        insert(const Iden& iden, const Type& value, Func comp);

        bool
        insert(const Iden& iden, const Type& value);

        template <class Func>
        bool
        insert(const Iden& iden, Type&& value, Func comp);

        bool
        insert(const Iden& iden, Type&& value);

        template <class Func>
        bool
        remove(const Iden& iden, Func comp);

        bool
        remove(const Iden& iden);

        Array<Type>&
        values();

        const Array<Type>&
        values() const;

        template <class Func>
        Type&
        find(const Iden& iden, Func comp);

        template <class Func>
        const Type&
        find(const Iden& iden, Func comp) const;

        Type&
        find(const Iden& iden);

        const Type&
        find(const Iden& iden) const;

        Type&
        operator[](const Iden& iden);

        const Type&
        operator[](const Iden& iden) const;

    private:
        inline static const usize s_empty =
            (usize) -1;

        struct Node
        {
            union
            {
                Iden iden = {};
            };

            usize dist = s_empty;
        };

        struct Entry
        {
            Type value;
            Node node;
        };

    private:
        usize
        index(const Iden& iden) const;

        usize
        next(usize index) const;

    private:
        Array<Node> m_nodes;
        Array<Type> m_array;

        usize m_count;
    };
} // namespace ma

#include <smal/Struct/impl/HashMap.tpp>

#endif // SMAL_STRUCT_DATA_HASH_MAP_HPP
