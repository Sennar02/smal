#include <smal/Algo/HashTable.hpp>

namespace ma
{
    template <class Name, class Item, class Layout>
    HashTable<Name, Item, Layout>::HashTable()
        : m_heads {}
        , m_array {}
        , m_count {0}
    { }

    template <class Name, class Item, class Layout>
    HashTable<Name, Item, Layout>::HashTable(const Layout& heads, const Layout& array)
        : m_heads {heads}
        , m_array {array}
        , m_count {0}
    { }

    template <class Name, class Item, class Layout>
    template <class... Args>
    HashTable<Name, Item, Layout>::HashTable(Args&&... args)
        : m_heads {forw<Args>(args)...}
        , m_array {forw<Args>(args)...}
        , m_count {0}
    { }

    template <class Name, class Item, class Layout>
    u32
    HashTable<Name, Item, Layout>::size() const
    {
        return m_array.length();
    }

    template <class Name, class Item, class Layout>
    u32
    HashTable<Name, Item, Layout>::count() const
    {
        return m_count;
    }

    template <class Name, class Item, class Layout>
    bool
    HashTable<Name, Item, Layout>::isEmpty() const
    {
        return m_count == 0;
    }

    template <class Name, class Item, class Layout>
    bool
    HashTable<Name, Item, Layout>::isFull() const
    {
        return m_count == m_array.length();
    }

    template <class Name, class Item, class Layout>
    template <class Func>
    u32
    HashTable<Name, Item, Layout>::indexOf(const Name& name, Func&& func) const
    {
        u32   hash = 0;
        Head* head = 0;

        if ( isEmpty() ) return g_max_u32;

        hash = code(name);

        for ( u32 i = hash; hash != next(i); i = next(i) ) {
            head = &m_heads[i];

            if ( head->dist != 0 && head->hash == hash ) {
                if ( func(head->name, name) == true )
                    return i;
            }
        }

        return g_max_u32;
    }

    template <class Name, class Item, class Layout>
    u32
    HashTable<Name, Item, Layout>::indexOf(const Name& name) const
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return indexOf(name, func);
    }

    template <class Name, class Item, class Layout>
    template <class Func>
    bool
    HashTable<Name, Item, Layout>::contains(const Name& name, Func&& func) const
    {
        u32 index = indexOf(name, func);

        if ( index < m_array.length() )
            return true;

        return false;
    }

    template <class Name, class Item, class Layout>
    bool
    HashTable<Name, Item, Layout>::contains(const Name& name) const
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return contains(name, func);
    }

    template <class Name, class Item, class Layout>
    template <class Iter, class Func>
    void
    HashTable<Name, Item, Layout>::forEach(Iter& iter, Func&& func) const
    {
        while ( iter.next() )
            func(iter.item(), iter.name());
    }

    template <class Name, class Item, class Layout>
    template <class Func>
    void
    HashTable<Name, Item, Layout>::forEach(Func&& func) const
    {
        HashTableForwIter iter = {*this};

        while ( iter.next() )
            func(iter.item(), iter.name());
    }

    template <class Name, class Item, class Layout>
    bool
    HashTable<Name, Item, Layout>::resize(u32 size)
    {
        bool flag = m_heads.resize(size) &&
                    m_array.resize(size);

        if ( flag == false ) return false;

        for ( u32 i = 0; next(i) != 0; i = next(i) ) {
            if ( m_heads[i].dist == 0 ) continue;

            if ( m_heads[i].hash != i ) {
                m_heads[i].dist = m_heads[i].hash = 0;

                if ( insert(m_heads[i].name, m_array[i].item) == false )
                    return false;
            }
        }

        return true;
    }

    template <class Name, class Item, class Layout>
    template <class Func>
    bool
    HashTable<Name, Item, Layout>::insert(const Name& name, const Item& item, Func&& func)
    {
        u32   hash = 0;
        Head  iter = {name};
        Body  elem = {item};
        Head* head = 0;

        if ( isFull() ) return false;

        hash      = code(name);
        iter.hash = hash;

        for ( u32 i = hash; true; i = next(i) ) {
            head = &m_heads[i];

            if ( head->dist != 0 && head->hash == hash ) {
                if ( func(head->name, name) )
                    return false;
            }

            if ( head->dist < iter.dist ) {
                if ( head->dist == 0 ) {
                    ctor(m_array[i], elem);
                    ctor(m_heads[i], iter);

                    m_count += 1u;

                    return true;
                }

                swap(m_heads[i], iter);
                swap(m_array[i], elem);
            }

            iter.dist += 1u;
        }

        return false;
    }

    template <class Name, class Item, class Layout>
    bool
    HashTable<Name, Item, Layout>::insert(const Name& name, const Item& item)
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return insert(name, item, func);
    }

    template <class Name, class Item, class Layout>
    template <class Func>
    bool
    HashTable<Name, Item, Layout>::remove(const Name& name, Func&& func)
    {
        u32 index = indexOf(name, func);

        if ( index < m_array.length() )
            m_heads[index].dist = 0;

        return index < m_array.length();
    }

    template <class Name, class Item, class Layout>
    bool
    HashTable<Name, Item, Layout>::remove(const Name& name)
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return remove(name, func);
    }

    template <class Name, class Item, class Layout>
    template <class Iter, class Func>
    void
    HashTable<Name, Item, Layout>::clear(Iter& iter, Func&& func)
    {
        while ( iter.next() )
            func(iter.item(), iter.name());

        m_count = 0;
    }

    template <class Name, class Item, class Layout>
    template <class Func>
    void
    HashTable<Name, Item, Layout>::clear(Func&& func)
    {
        HashTableForwIter iter = {*this};

        while ( iter.next() )
            func(iter.item(), iter.name());

        m_count = 0;
    }

    template <class Name, class Item, class Layout>
    void
    HashTable<Name, Item, Layout>::clear()
    {
        m_count = 0;
    }

    template <class Name, class Item, class Layout>
    template <class Func>
    Item&
    HashTable<Name, Item, Layout>::find(const Name& name, Item& deflt, Func&& func) const
    {
        u32 index = indexOf(name, func);

        if ( index < m_array.length() )
            return m_array[index].item;

        return deflt;
    }

    template <class Name, class Item, class Layout>
    Item&
    HashTable<Name, Item, Layout>::find(const Name& name, Item& deflt) const
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return find(name, deflt, func);
    }

    template <class Name, class Item, class Layout>
    template <class Func>
    Item&
    HashTable<Name, Item, Layout>::find(const Name& name, Func&& func) const
    {
        return m_array[indexOf(name, func)].item;
    }

    template <class Name, class Item, class Layout>
    Item&
    HashTable<Name, Item, Layout>::find(const Name& name) const
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return find(name, func);
    }

    template <class Name, class Item, class Layout>
    const Array<HashHead<Name>, Layout>&
    HashTable<Name, Item, Layout>::heads() const
    {
        return m_heads;
    }

    template <class Name, class Item, class Layout>
    const Array<HashBody<Item>, Layout>&
    HashTable<Name, Item, Layout>::array() const
    {
        return m_array;
    }

    template <class Name, class Item, class Layout>
    Item&
    HashTable<Name, Item, Layout>::operator[](const Name& name) const
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return find(name, func);
    }

    template <class Name, class Item, class Layout>
    u32
    HashTable<Name, Item, Layout>::code(const Name& name) const
    {
        return next(hash(name), 0);
    }

    template <class Name, class Item, class Layout>
    u32
    HashTable<Name, Item, Layout>::next(u32 code, u32 step) const
    {
        u32 div = m_array.length();

        if ( div != 0 )
            return (code + step) % div;

        return 0;
    }

    template <class Name, class Item, class Layout>
    HashTableForwIter<Name, Item, Layout>::HashTableForwIter(const Table& table)
        : m_table {table}
        , m_index {g_max_u32}
    { }

    template <class Name, class Item, class Layout>
    const Name&
    HashTableForwIter<Name, Item, Layout>::name() const
    {
        return m_table.heads()[m_index].name;
    }

    template <class Name, class Item, class Layout>
    Item&
    HashTableForwIter<Name, Item, Layout>::item()
    {
        return m_table.array()[m_index].item;
    }

    template <class Name, class Item, class Layout>
    const Item&
    HashTableForwIter<Name, Item, Layout>::item() const
    {
        return m_table.array()[m_index].item;
    }

    template <class Name, class Item, class Layout>
    bool
    HashTableForwIter<Name, Item, Layout>::hasNext() const
    {
        u32 i = m_index;

        while ( ++i < m_table.size() ) {
            if ( m_table.heads()[i].dist != 0 )
                return true;
        }

        return false;
    }

    template <class Name, class Item, class Layout>
    bool
    HashTableForwIter<Name, Item, Layout>::next()
    {
        u32& i = m_index;

        while ( ++i < m_table.size() ) {
            if ( m_table.heads()[i].dist != 0 )
                return true;
        }

        return false;
    }

    template <class Name, class Item, class Layout>
    void
    HashTableForwIter<Name, Item, Layout>::reset()
    {
        m_index = g_max_u32;
    }
} // namespace ma
