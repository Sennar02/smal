#ifndef SMAL_ALGO_HASH_TABLE_HPP
#define SMAL_ALGO_HASH_TABLE_HPP

#include <smal/Algo/define.hpp>

namespace ma
{
    namespace impl
    {
        template <class Name>
        struct Head;
    } // namespace impl

    template <class Name, class Item, template <class> class Array = FixedBuffer>
    class HashTable
    {
    public:
        using Head = impl::Head<Name>;

        /**
         *
         */
        HashTable();

        /**
         *
         */
        HashTable(Array<Head>&& heads, Array<Item>&& array);

        /**
         *
         */
        template <class... Args>
        HashTable(BaseOrigin& origin, u32 size, Args&&... args);

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
        const Array<Head>&
        heads() const;

        /**
         *
         */
        const Array<Item>&
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
        next(u32 code) const;

    private:
        /**
         *
         */
        Array<Head> m_heads;

        /**
         *
         */
        Array<Item> m_array;

        /**
         *
         */
        u32 m_count;
    };

    template <class Name, class Item, template <class> class Array>
    class HashTableForwIter
    {
    private:
        using Table = HashTable<Name, Item, Array>;

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

    template <class Name, class Item, template <class> class Array>
    HashTableForwIter(HashTable<Name, Item, Array>&)
        -> HashTableForwIter<Name, Item, Array>;
} // namespace ma

#include <smal/Algo/inline/HashTable.inl>

#endif // SMAL_ALGO_HASH_TABLE_HPP
