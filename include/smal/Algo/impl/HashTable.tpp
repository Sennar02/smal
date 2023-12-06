#include <smal/Algo/HashTable.hpp>

namespace ma
{
    template <class Name, class Item, template <class> class Block>
    HashTable<Name, Item, Block>::HashTable()
        : m_nodes {}
        , m_block {}
        , m_count {0}
    { }

    template <class Name, class Item, template <class> class Block>
    HashTable<Name, Item, Block>::HashTable(const Block<Node>& nodes, const Block<Item>& block)
        : m_nodes {nodes}
        , m_block {block}
        , m_count {0}
    { }

    template <class Name, class Item, template <class> class Block>
    template <class Alloc>
    HashTable<Name, Item, Block>::HashTable(Alloc& alloc, u32 size)
        : HashTable({alloc, size}, {alloc, size})
    { }

    template <class Name, class Item, template <class> class Block>
    u32
    HashTable<Name, Item, Block>::size() const
    {
        if constexpr ( sizeof(Node) < sizeof(Item) )
            return m_block.size();
        else
            return m_nodes.size();
    }

    template <class Name, class Item, template <class> class Block>
    u32
    HashTable<Name, Item, Block>::count() const
    {
        return m_count;
    }

    template <class Name, class Item, template <class> class Block>
    bool
    HashTable<Name, Item, Block>::isEmpty() const
    {
        return m_count == 0;
    }

    template <class Name, class Item, template <class> class Block>
    bool
    HashTable<Name, Item, Block>::isFull() const
    {
        return m_count == size();
    }

    template <class Name, class Item, template <class> class Block>
    template <class Func>
    u32
    HashTable<Name, Item, Block>::indexOf(const Name& name, Func&& func) const
    {
        u32 hash = code(name);

        if ( isEmpty() ) return g_max_u32;

        for ( u32 i = hash; hash != next(i); i = next(i) ) {
            if ( m_nodes[i].dist == 0 ) break;

            if ( code(m_nodes[i].name) == hash ) {
                if ( func(m_nodes[i].name, name) == true )
                    return i;
            }
        }

        return g_max_u32;
    }

    template <class Name, class Item, template <class> class Block>
    u32
    HashTable<Name, Item, Block>::indexOf(const Name& name) const
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return indexOf(name, func);
    }

    template <class Name, class Item, template <class> class Block>
    template <class Func>
    bool
    HashTable<Name, Item, Block>::contains(const Name& name, Func&& func) const
    {
        return indexOf(name, func) < m_count;
    }

    template <class Name, class Item, template <class> class Block>
    bool
    HashTable<Name, Item, Block>::contains(const Name& name) const
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return contains(name, func);
    }

    template <class Name, class Item, template <class> class Block>
    template <class Iter, class Func>
    void
    HashTable<Name, Item, Block>::forEach(Iter& iter, Func&& func) const
    {
        while ( true ) {
            func(iter.name(), iter.item());

            if ( iter.next() == false )
                break;
        }
    }

    template <class Name, class Item, template <class> class Block>
    template <class Func>
    bool
    HashTable<Name, Item, Block>::insert(const Name& name, const Item& item, Func&& func)
    {
        Node node = {name, 1};
        u32  hash = code(name);
        u32  dist = 0;

        if ( isFull() ) return false;

        for ( u32 i = hash; hash != next(i); i = next(i) ) {
            dist = m_nodes[i].dist;

            if ( dist != 0 && code(m_nodes[i].name) == hash )
                return func(m_nodes[i].name, name) == true;

            if ( dist < node.dist ) {
                if ( dist == 0 ) {
                    m_nodes[i] = node;
                    m_block[i] = item;
                    m_count += 1;

                    return true;
                }

                swap(m_nodes[i], node);
                swap(m_block[i], (Item&) item);
            }

            node.dist += 1;
        }

        return false;
    }

    template <class Name, class Item, template <class> class Block>
    bool
    HashTable<Name, Item, Block>::insert(const Name& name, const Item& item)
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return insert(name, item, func);
    }

    template <class Name, class Item, template <class> class Block>
    template <class Func>
    bool
    HashTable<Name, Item, Block>::remove(const Name& name, Func&& func)
    {
        u32 index = indexOf(name, func);
        u32 count = size();

        if ( index < count ) {
            m_count -= 1;
            m_nodes[index].dist = 0;

            return true;
        }

        return false;
    }

    template <class Name, class Item, template <class> class Block>
    bool
    HashTable<Name, Item, Block>::remove(const Name& name)
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return remove(name, func);
    }

    template <class Name, class Item, template <class> class Block>
    template <class Func>
    Item*
    HashTable<Name, Item, Block>::search(const Name& name, Func&& func) const
    {
        u32 index = indexOf(name, func);
        u32 count = size();

        if ( index < count )
            return &m_block[index];

        return 0;
    }

    template <class Name, class Item, template <class> class Block>
    Item*
    HashTable<Name, Item, Block>::search(const Name& name) const
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return search(name, func);
    }

    template <class Name, class Item, template <class> class Block>
    Item&
    HashTable<Name, Item, Block>::find(const Name& name) const
    {
        return *search(name);
    }

    template <class Name, class Item, template <class> class Block>
    const Block<HashNode<Name>>&
    HashTable<Name, Item, Block>::nodes() const
    {
        return m_nodes;
    }

    template <class Name, class Item, template <class> class Block>
    const Block<Item>&
    HashTable<Name, Item, Block>::block() const
    {
        return m_block;
    }

    template <class Name, class Item, template <class> class Block>
    Item&
    HashTable<Name, Item, Block>::operator[](const Name& name) const
    {
        return find(name);
    }

    template <class Name, class Item, template <class> class Block>
    u32
    HashTable<Name, Item, Block>::code(const Name& name) const
    {
        u32 div = size();

        if ( div != 0 )
            return hash(name) % div;

        return 0;
    }

    template <class Name, class Item, template <class> class Block>
    u32
    HashTable<Name, Item, Block>::next(u32 code) const
    {
        u32 div = size();

        if ( div != 0 )
            return (code + 1) % div;

        return 0;
    }

    template <class Name, class Item, template <class> class Block>
    HashTableForwIter<Name, Item, Block>::HashTableForwIter(const Table& table)
        : m_table {table}
        , m_index {0}
    {
        clear();
    }

    template <class Name, class Item, template <class> class Block>
    const Name&
    HashTableForwIter<Name, Item, Block>::name() const
    {
        return m_table.nodes()[m_index].name;
    }

    template <class Name, class Item, template <class> class Block>
    Item&
    HashTableForwIter<Name, Item, Block>::item()
    {
        return m_table.block()[m_index];
    }

    template <class Name, class Item, template <class> class Block>
    const Item&
    HashTableForwIter<Name, Item, Block>::item() const
    {
        return m_table.block()[m_index];
    }

    template <class Name, class Item, template <class> class Block>
    bool
    HashTableForwIter<Name, Item, Block>::hasNext() const
    {
        u32 size = m_table.size();
        u32 next = m_index + 1;

        for ( u32 i = next; i < size; i++ ) {
            if ( m_table.nodes()[i].dist != 0 )
                return true;
        }

        return false;
    }

    template <class Name, class Item, template <class> class Block>
    bool
    HashTableForwIter<Name, Item, Block>::next()
    {
        u32 size = m_table.size();

        for ( u32& i = ++m_index; i < size; i++ ) {
            if ( m_table.nodes()[i].dist != 0 )
                return true;
        }

        return false;
    }

    template <class Name, class Item, template <class> class Block>
    void
    HashTableForwIter<Name, Item, Block>::clear()
    {
        m_index = 0, next();
    }
} // namespace ma
