#ifndef SMAL_ALGO_HASH_TABLE_HPP
#define SMAL_ALGO_HASH_TABLE_HPP

#include <smal/Algo/define.hpp>

namespace ma
{
    template <class Name>
    struct HashNode
    {
        union
        {
            Name name;
        };

        u32 dist;
    };

    inline static auto g_true =
        action([]() { return true; });

    template <class Name, class Item, template <class> class Block = PagedBlock>
    class HashTable
    {
    public:
        using Node = HashNode<Name>;

    public:
        /**
         *
         */
        HashTable();

        /**
         *
         */
        HashTable(const Block<Node>& nodes, const Block<Item>& block);

        /**
         *
         */
        template <class Alloc>
        HashTable(Alloc& alloc, u32 size);

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
        template <class Func>
        Item*
        search(const Name& name, Func&& func) const;

        /**
         *
         */
        Item*
        search(const Name& name) const;

        /**
         *
         */
        Item&
        find(const Name& name) const;

        /**
         *
         */
        const Block<Node>&
        nodes() const;

        /**
         *
         */
        const Block<Item>&
        block() const;

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
        Block<Node> m_nodes;

        /**
         *
         */
        Block<Item> m_block;

        /**
         *
         */
        u32 m_count;
    };

    template <class Name, class Item, template <class> class Block>
    HashTable(const Block<HashNode<Name>>&, const Block<Item>&)
        -> HashTable<Name, Item, Block>;

    template <class Name, class Item, template <class> class Block>
    class HashTableForwIter
    {
    private:
        using Table = HashTable<Name, Item, Block>;

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
        clear();

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

    template <class Name, class Item, template <class> class Block>
    HashTableForwIter(HashTable<Name, Item, Block>&)
        -> HashTableForwIter<Name, Item, Block>;
} // namespace ma

#include <smal/Algo/impl/HashTable.tpp>

#endif // SMAL_ALGO_HASH_TABLE_HPP
