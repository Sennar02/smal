#include <smal/Algo/HashTable.hpp>

namespace ma
{
    namespace impl
    {
        template <class Name>
        struct Head
        {
            union
            {
                Name name;
            };

            u32 dist;
        };
    } // namespace impl

    template <class Name, class Item, template <class> class Array>
    HashTable<Name, Item, Array>::HashTable()
        : m_heads {}
        , m_array {}
        , m_count {0}
    { }

    template <class Name, class Item, template <class> class Array>
    HashTable<Name, Item, Array>::HashTable(Array<impl::Head<Name>>&& heads, Array<Item>&& array)
        : m_heads {heads}
        , m_array {array}
        , m_count {0}
    { }

    template <class Name, class Item, template <class> class Array>
    template <class... Args>
    HashTable<Name, Item, Array>::HashTable(BaseOrigin& origin, u32 size, Args&&... args)
        : m_heads {origin, size, forw<Args>(args)...}
        , m_array {origin, size, forw<Args>(args)...}
        , m_count {0}
    { }

    template <class Name, class Item, template <class> class Array>
    u32
    HashTable<Name, Item, Array>::size() const
    {
        if constexpr ( sizeof(Head) < sizeof(Item) )
            return m_array.size();
        else
            return m_heads.size();
    }

    template <class Name, class Item, template <class> class Array>
    u32
    HashTable<Name, Item, Array>::count() const
    {
        return m_count;
    }

    template <class Name, class Item, template <class> class Array>
    bool
    HashTable<Name, Item, Array>::isEmpty() const
    {
        return m_count == 0;
    }

    template <class Name, class Item, template <class> class Array>
    bool
    HashTable<Name, Item, Array>::isFull() const
    {
        return m_count == size();
    }

    template <class Name, class Item, template <class> class Array>
    template <class Func>
    u32
    HashTable<Name, Item, Array>::indexOf(const Name& name, Func&& func) const
    {
        u32 hash = code(name);

        if ( isEmpty() ) return g_max_u32;

        for ( u32 i = hash; hash != next(i); i = next(i) ) {
            if ( m_heads[i].dist == 0 ) break;

            if ( code(m_heads[i].name) == hash ) {
                if ( func(m_heads[i].name, name) == true )
                    return i;
            }
        }

        return g_max_u32;
    }

    template <class Name, class Item, template <class> class Array>
    u32
    HashTable<Name, Item, Array>::indexOf(const Name& name) const
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return indexOf(name, func);
    }

    template <class Name, class Item, template <class> class Array>
    template <class Func>
    bool
    HashTable<Name, Item, Array>::contains(const Name& name, Func&& func) const
    {
        return indexOf(name, func) < size();
    }

    template <class Name, class Item, template <class> class Array>
    bool
    HashTable<Name, Item, Array>::contains(const Name& name) const
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return indexOf(name, func) < size();
    }

    template <class Name, class Item, template <class> class Array>
    template <class Iter, class Func>
    void
    HashTable<Name, Item, Array>::forEach(Iter& iter, Func&& func) const
    {
        while ( iter.next() )
            func(iter.name(), iter.item());
    }

    template <class Name, class Item, template <class> class Array>
    template <class Func>
    void
    HashTable<Name, Item, Array>::forEach(Func&& func) const
    {
        HashTableForwIter iter = {*this};

        while ( iter.next() )
            func(iter.name(), iter.item());
    }

    template <class Name, class Item, template <class> class Array>
    bool
    HashTable<Name, Item, Array>::resize(u32 size)
    {
        bool flag = m_heads.resize(size) &&
                    m_array.resize(size);

        if ( flag == false ) return false;

        for ( u32 i = 0; next(i) != 0; i = next(i) ) {
            if ( m_heads[i].dist == 0 ) continue;

            if ( code(m_heads[i].name) != i ) {
                m_heads[i].dist = 0;

                if ( insert(m_heads[i].name, m_array[i]) == false )
                    return false;
            }
        }

        return true;
    }

    template <class Name, class Item, template <class> class Array>
    template <class Func>
    bool
    HashTable<Name, Item, Array>::insert(const Name& name, const Item& item, Func&& func)
    {
        Head head = {name, 1u};
        u32  hash = code(name);
        u32  dist = 0;

        if ( isFull() ) return false;

        for ( u32 i = hash; hash != next(i); i = next(i) ) {
            dist = m_heads[i].dist;

            if ( dist != 0 && code(m_heads[i].name) == hash )
                return func(m_heads[i].name, name) == true;

            if ( dist < head.dist ) {
                if ( dist == 0 ) {
                    ctor(m_heads[i], head);
                    ctor(m_array[i], item);
                    m_count += 1u;

                    return true;
                }

                swap(m_heads[i], head);
                swap(m_array[i], (Item&) item);
            }

            head.dist += 1u;
        }

        return false;
    }

    template <class Name, class Item, template <class> class Array>
    bool
    HashTable<Name, Item, Array>::insert(const Name& name, const Item& item)
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return insert(name, item, func);
    }

    template <class Name, class Item, template <class> class Array>
    template <class Func>
    bool
    HashTable<Name, Item, Array>::remove(const Name& name, Func&& func)
    {
        u32 index = indexOf(name, func);
        u32 count = size();

        if ( index < count ) {
            m_count -= 1u;
            m_heads[index].dist = 0;

            return true;
        }

        return false;
    }

    template <class Name, class Item, template <class> class Array>
    bool
    HashTable<Name, Item, Array>::remove(const Name& name)
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return remove(name, func);
    }

    template <class Name, class Item, template <class> class Array>
    template <class Iter, class Func>
    void
    HashTable<Name, Item, Array>::clear(Iter& iter, Func&& func)
    {
        while ( iter.next() )
            func(iter.name(), iter.item());

        m_count = 0;
    }

    template <class Name, class Item, template <class> class Array>
    template <class Func>
    void
    HashTable<Name, Item, Array>::clear(Func&& func)
    {
        HashTableForwIter iter = {*this};

        while ( iter.next() )
            func(iter.name(), iter.item());

        m_count = 0;
    }

    template <class Name, class Item, template <class> class Array>
    void
    HashTable<Name, Item, Array>::clear()
    {
        m_count = 0;
    }

    template <class Name, class Item, template <class> class Array>
    template <class Func>
    Item*
    HashTable<Name, Item, Array>::search(const Name& name, Func&& func) const
    {
        u32 index = indexOf(name, func);
        u32 count = size();

        if ( index < count )
            return &m_array[index];

        return 0;
    }

    template <class Name, class Item, template <class> class Array>
    Item*
    HashTable<Name, Item, Array>::search(const Name& name) const
    {
        auto func = [](const Name& a, const Name& b) {
            return a == b;
        };

        return search(name, func);
    }

    template <class Name, class Item, template <class> class Array>
    template <class Func>
    Item&
    HashTable<Name, Item, Array>::find(const Name& name, Func&& func) const
    {
        return *search(name, func);
    }

    template <class Name, class Item, template <class> class Array>
    Item&
    HashTable<Name, Item, Array>::find(const Name& name) const
    {
        return *search(name);
    }

    template <class Name, class Item, template <class> class Array>
    const Array<impl::Head<Name>>&
    HashTable<Name, Item, Array>::heads() const
    {
        return m_heads;
    }

    template <class Name, class Item, template <class> class Array>
    const Array<Item>&
    HashTable<Name, Item, Array>::array() const
    {
        return m_array;
    }

    template <class Name, class Item, template <class> class Array>
    Item&
    HashTable<Name, Item, Array>::operator[](const Name& name) const
    {
        return *search(name);
    }

    template <class Name, class Item, template <class> class Array>
    u32
    HashTable<Name, Item, Array>::code(const Name& name) const
    {
        u32 div = size();

        if ( div != 0 )
            return hash(name) % div;

        return 0;
    }

    template <class Name, class Item, template <class> class Array>
    u32
    HashTable<Name, Item, Array>::next(u32 code) const
    {
        u32 div = size();

        if ( div != 0 )
            return (code + 1u) % div;

        return 0;
    }

    template <class Name, class Item, template <class> class Array>
    HashTableForwIter<Name, Item, Array>::HashTableForwIter(const Table& table)
        : m_table {table}
        , m_index {g_max_u32}
    { }

    template <class Name, class Item, template <class> class Array>
    const Name&
    HashTableForwIter<Name, Item, Array>::name() const
    {
        return m_table.heads()[m_index].name;
    }

    template <class Name, class Item, template <class> class Array>
    Item&
    HashTableForwIter<Name, Item, Array>::item()
    {
        return m_table.array()[m_index];
    }

    template <class Name, class Item, template <class> class Array>
    const Item&
    HashTableForwIter<Name, Item, Array>::item() const
    {
        return m_table.array()[m_index];
    }

    template <class Name, class Item, template <class> class Array>
    bool
    HashTableForwIter<Name, Item, Array>::hasNext() const
    {
        u32 size = m_table.size();
        u32 next = m_index + 1u;

        for ( u32 i = next; i < size; i++ ) {
            if ( m_table.heads()[i].dist != 0 )
                return true;
        }

        return false;
    }

    template <class Name, class Item, template <class> class Array>
    bool
    HashTableForwIter<Name, Item, Array>::next()
    {
        u32 size = m_table.size();

        for ( u32& i = ++m_index; i < size; i++ ) {
            if ( m_table.heads()[i].dist != 0 )
                return true;
        }

        return false;
    }

    template <class Name, class Item, template <class> class Array>
    void
    HashTableForwIter<Name, Item, Array>::reset()
    {
        m_index = g_max_u32;
    }
} // namespace ma
