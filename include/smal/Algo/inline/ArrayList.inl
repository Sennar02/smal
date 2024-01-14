#include <smal/Algo/ArrayList.hpp>

namespace ma
{
    template <class Item, class Layout>
    ArrayList<Item, Layout>::ArrayList()
        : m_array {}
        , m_count {0}
    { }

    template <class Item, class Layout>
    ArrayList<Item, Layout>::ArrayList(const Layout& array)
        : m_array {array}
        , m_count {0}
    { }

    template <class Item, class Layout>
    template <class... Args>
    ArrayList<Item, Layout>::ArrayList(Args&&... args)
        : m_array {forw<Args>(args)...}
        , m_count {0}
    { }

    template <class Item, class Layout>
    u32
    ArrayList<Item, Layout>::size() const
    {
        return m_array.length();
    }

    template <class Item, class Layout>
    u32
    ArrayList<Item, Layout>::count() const
    {
        return m_count;
    }

    template <class Item, class Layout>
    bool
    ArrayList<Item, Layout>::isEmpty() const
    {
        return m_count == 0;
    }

    template <class Item, class Layout>
    bool
    ArrayList<Item, Layout>::isFull() const
    {
        return m_count == m_array.length();
    }

    template <class Item, class Layout>
    template <class Iter, class Func>
    u32
    ArrayList<Item, Layout>::indexOf(const Item& item, Iter& iter, Func&& func) const
    {
        while ( iter.next() ) {
            if ( func(iter.item(), item) == true )
                return iter.index();
        }

        return g_max_u32;
    }

    template <class Item, class Layout>
    template <class Func>
    u32
    ArrayList<Item, Layout>::indexOf(const Item& item, Func&& func) const
    {
        ArrayListForwIter iter = {*this};

        while ( iter.next() ) {
            if ( func(iter.item(), item) == true )
                return iter.index();
        }

        return g_max_u32;
    }

    template <class Item, class Layout>
    u32
    ArrayList<Item, Layout>::indexOf(const Item& item) const
    {
        auto func = [](const Item& a, const Item& b) {
            return a == b;
        };

        return indexOf(item, func);
    }

    template <class Item, class Layout>
    template <class Iter, class Func>
    bool
    ArrayList<Item, Layout>::contains(const Item& item, Iter& iter, Func&& func) const
    {
        return indexOf(item, iter, func) < m_count;
    }

    template <class Item, class Layout>
    template <class Func>
    bool
    ArrayList<Item, Layout>::contains(const Item& item, Func&& func) const
    {
        ArrayListForwIter iter = {*this};

        return indexOf(item, iter, func) < m_count;
    }

    template <class Item, class Layout>
    bool
    ArrayList<Item, Layout>::contains(const Item& item) const
    {
        auto func = [](const Item& a, const Item& b) {
            return a == b;
        };

        return contains(item, func);
    }

    template <class Item, class Layout>
    template <class Iter, class Func>
    void
    ArrayList<Item, Layout>::forEach(Iter& iter, Func&& func) const
    {
        while ( iter.next() )
            func(iter.item(), iter.index());
    }

    template <class Item, class Layout>
    template <class Func>
    void
    ArrayList<Item, Layout>::forEach(Func&& func) const
    {
        ArrayListForwIter iter = {*this};

        while ( iter.next() )
            func(iter.item(), iter.index());
    }

    template <class Item, class Layout>
    bool
    ArrayList<Item, Layout>::resize(u32 size)
    {
        return m_array.resize(size);
    }

    template <class Item, class Layout>
    bool
    ArrayList<Item, Layout>::insert(const Item& item, u32 index)
    {
        if ( isFull() ) return false;

        if ( index > m_count ) index = m_count;

        for ( u32 i = m_count; i > index; i-- )
            m_array[i] = move(m_array[i - 1u]);

        m_count += 1u;

        ctor(m_array[index], item);

        return true;
    }

    template <class Item, class Layout>
    bool
    ArrayList<Item, Layout>::remove(u32 index)
    {
        if ( isEmpty() ) return false;

        if ( index >= m_count ) index = m_count - 1u;

        for ( u32 i = index; i < m_count - 1u; i++ )
            m_array[i] = move(m_array[i + 1u]);

        m_count -= 1u;

        return true;
    }

    template <class Item, class Layout>
    template <class Iter, class Func>
    void
    ArrayList<Item, Layout>::clear(Iter& iter, Func&& func)
    {
        while ( iter.next() )
            func(iter.item(), iter.index());

        m_count = 0;
    }

    template <class Item, class Layout>
    template <class Func>
    void
    ArrayList<Item, Layout>::clear(Func&& func)
    {
        ArrayListForwIter iter = {*this};

        while ( iter.next() )
            func(iter.item(), iter.index());

        m_count = 0;
    }

    template <class Item, class Layout>
    void
    ArrayList<Item, Layout>::clear()
    {
        m_count = 0;
    }

    template <class Item, class Layout>
    Item&
    ArrayList<Item, Layout>::find(u32 index, Item& deflt) const
    {
        if ( index < m_count )
            return m_array[index];

        return deflt;
    }

    template <class Item, class Layout>
    Item&
    ArrayList<Item, Layout>::find(u32 index) const
    {
        return m_array[index];
    }

    template <class Item, class Layout>
    const Array<Item, Layout>&
    ArrayList<Item, Layout>::array() const
    {
        return m_array;
    }

    template <class Item, class Layout>
    Item&
    ArrayList<Item, Layout>::operator[](u32 index) const
    {
        return m_array[index];
    }

    template <class Item, class Layout>
    ArrayListForwIter<Item, Layout>::ArrayListForwIter(const List& list)
        : m_list {list}
        , m_index {g_max_u32}
    { }

    template <class Item, class Layout>
    u32
    ArrayListForwIter<Item, Layout>::index() const
    {
        return m_index;
    }

    template <class Item, class Layout>
    Item&
    ArrayListForwIter<Item, Layout>::item()
    {
        return m_list.array()[m_index];
    }

    template <class Item, class Layout>
    const Item&
    ArrayListForwIter<Item, Layout>::item() const
    {
        return m_list.array()[m_index];
    }

    template <class Item, class Layout>
    bool
    ArrayListForwIter<Item, Layout>::hasNext() const
    {
        u32 next = m_index + 1u;

        if ( next < m_list.count() )
            return true;

        return false;
    }

    template <class Item, class Layout>
    bool
    ArrayListForwIter<Item, Layout>::next()
    {
        u32 next = m_index + 1u;

        if ( next < m_list.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, class Layout>
    void
    ArrayListForwIter<Item, Layout>::reset()
    {
        m_index = g_max_u32;
    }

    template <class Item, class Layout>
    ArrayListBackIter<Item, Layout>::ArrayListBackIter(const List& list)
        : m_list {list}
        , m_index {g_max_u32}
    { }

    template <class Item, class Layout>
    u32
    ArrayListBackIter<Item, Layout>::index() const
    {
        return m_index;
    }

    template <class Item, class Layout>
    Item&
    ArrayListBackIter<Item, Layout>::item()
    {
        u32 index = m_list.count() -
                    m_index;

        return m_list.find(index - 1u);
    }

    template <class Item, class Layout>
    const Item&
    ArrayListBackIter<Item, Layout>::item() const
    {
        u32 index = m_list.count() -
                    m_index;

        return m_list.find(index - 1u);
    }

    template <class Item, class Layout>
    bool
    ArrayListBackIter<Item, Layout>::hasNext() const
    {
        u32 next = m_index + 1u;

        if ( next < m_list.count() )
            return true;

        return false;
    }

    template <class Item, class Layout>
    bool
    ArrayListBackIter<Item, Layout>::next()
    {
        u32 next = m_index + 1u;

        if ( next < m_list.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, class Layout>
    void
    ArrayListBackIter<Item, Layout>::reset()
    {
        m_index = g_max_u32;
    }
} // namespace ma
