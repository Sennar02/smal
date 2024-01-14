#ifndef SMAL_ALGO_HASH_TABLE_HPP
#define SMAL_ALGO_HASH_TABLE_HPP

#include <smal/Algo/define.hpp>

namespace ma
{
    template <class Name>
    struct HashHead
    {
        Name name;
        u32  hash = 0;
        u32  dist = 1u;
    };

    template <class Item>
    struct HashBody
    {
        Item item;
    };

    template <class Name, class Item, class Layout = FixedLayout>
    class HashTable
    {
    public:
        using Head = HashHead<Name>;
        using Body = HashBody<Item>;

    public:
        /**
         *
         */
        HashTable();

        /**
         *
         */
        HashTable(const Layout& heads, const Layout& array);

        /**
         *
         */
        template <class... Args>
        HashTable(Args&&... args);

        /**
         *
         */
        virtual ~HashTable() = default;

        /**
         *
         */
        u32
        size() const;

        /**
         *
         */
        u32
        count() const;

        /**
         *
         */
        bool
        isEmpty() const;

        /**
         *
         */
        bool
        isFull() const;

        /**
         *
         */
        template <class Func>
        bool
        contains(const Name& name, Func&& func) const;

        /**
         *
         */
        bool
        contains(const Name& name) const;

        /**
         *
         */
        template <class Iter, class Func>
        void
        forEach(Iter& iter, Func&& func) const;

        /**
         *
         */
        template <class Func>
        void
        forEach(Func&& func) const;

        /**
         *
         */
        bool
        resize(u32 size);

        /**
         *
         */
        template <class Func>
        bool
        insert(const Name& name, const Item& item, Func&& func);

        /**
         *
         */
        bool
        insert(const Name& name, const Item& item);

        /**
         *
         */
        template <class Func>
        bool
        remove(const Name& name, Func&& func);

        /**
         *
         */
        bool
        remove(const Name& name);

        /**
         *
         */
        template <class Iter, class Func>
        void
        clear(Iter& iter, Func&& func);

        /**
         *
         */
        template <class Func>
        void
        clear(Func&& func);

        /**
         *
         */
        void
        clear();

        /**
         *
         */
        template <class Func>
        Item&
        find(const Name& name, Item& deflt, Func&& func) const;

        /**
         *
         */
        Item&
        find(const Name& name, Item& deflt) const;

        /**
         *
         */
        template <class Func>
        Item&
        find(const Name& name, Func&& func) const;

        /**
         *
         */
        Item&
        find(const Name& name) const;

        /**
         *
         */
        const Array<HashHead<Name>, Layout>&
        heads() const;

        /**
         *
         */
        const Array<HashBody<Item>, Layout>&
        array() const;

        /**
         *
         */
        Item&
        operator[](const Name& name) const;

    private:
        /**
         *
         */
        template <class Func>
        u32
        indexOf(const Name& name, Func&& func) const;

        /**
         *
         */
        u32
        indexOf(const Name& name) const;

        /**
         *
         */
        u32
        code(const Name& name) const;

        /**
         *
         */
        u32
        next(u32 code, u32 step = 1u) const;

    private:
        /**
         *
         */
        Array<HashHead<Name>, Layout> m_heads;

        /**
         *
         */
        Array<HashBody<Item>, Layout> m_array;

        /**
         *
         */
        u32 m_count;
    };

    template <class Name, class Item, class Layout>
    class HashTableForwIter
    {
    private:
        using Table = HashTable<Name, Item, Layout>;

    public:
        /**
         *
         */
        HashTableForwIter(const Table& table);

        /**
         *
         */
        const Name&
        name() const;

        /**
         *
         */
        Item&
        item();

        /**
         *
         */
        const Item&
        item() const;

        /**
         *
         */
        bool
        hasNext() const;

        /**
         *
         */
        bool
        next();

        /**
         *
         */
        void
        reset();

    private:
        /**
         *
         */
        const Table& m_table;

        /**
         *
         */
        u32 m_index;
    };

    template <class Name, class Item, class Layout>
    HashTable(const Layout&, const Layout&)
        -> HashTable<Name, Item, Layout>;

    template <class Name, class Item, class Layout>
    HashTableForwIter(const HashTable<Name, Item, Layout>&)
        -> HashTableForwIter<Name, Item, Layout>;
} // namespace ma

#include <smal/Algo/inline/HashTable.inl>

#endif // SMAL_ALGO_HASH_TABLE_HPP
