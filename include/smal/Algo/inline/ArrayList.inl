#include <smal/Algo/ArrayList.hpp>

namespace ma
{
    template <class Item, template <class> class Array>
    ArrayList<Item, Array>::ArrayList()
        : m_array {}
        , m_count {0}
    { }

    template <class Item, template <class> class Array>
    ArrayList<Item, Array>::ArrayList(Array<Item>&& array)
        : m_array {move(array)}
        , m_count {0}
    { }

    template <class Item, template <class> class Array>
    template <class... Args>
    ArrayList<Item, Array>::ArrayList(BaseOrigin& origin, u32 size, Args&&... args)
        : m_array {origin, size, forw<Args>(args)...}
        , m_count {0}
    { }

    template <class Item, template <class> class Array>
    u32
    ArrayList<Item, Array>::size() const
    {
        return m_array.size();
    }

    template <class Item, template <class> class Array>
    u32
    ArrayList<Item, Array>::count() const
    {
        return m_count;
    }

    template <class Item, template <class> class Array>
    bool
    ArrayList<Item, Array>::isEmpty() const
    {
        return m_count == 0;
    }

    template <class Item, template <class> class Array>
    bool
    ArrayList<Item, Array>::isFull() const
    {
        return m_count == size();
    }

    template <class Item, template <class> class Array>
    template <class Iter, class Func>
    u32
    ArrayList<Item, Array>::indexOf(const Item& item, Iter& iter, Func&& func) const
    {
        while ( iter.next() ) {
            if ( func(iter.item(), item) == true )
                return iter.index();
        }

        return g_max_u32;
    }

    template <class Item, template <class> class Array>
    template <class Func>
    u32
    ArrayList<Item, Array>::indexOf(const Item& item, Func&& func) const
    {
        ArrayListForwIter iter = {*this};

        while ( iter.next() ) {
            if ( func(iter.item(), item) == true )
                return iter.index();
        }

        return g_max_u32;
    }

    template <class Item, template <class> class Array>
    u32
    ArrayList<Item, Array>::indexOf(const Item& item) const
    {
        auto func = [](const Item& a, const Item& b) {
            return a == b;
        };

        return indexOf(item, func);
    }

    template <class Item, template <class> class Array>
    template <class Iter, class Func>
    bool
    ArrayList<Item, Array>::contains(const Item& item, Iter& iter, Func&& func) const
    {
        return indexOf(item, iter, func) < m_count;
    }

    template <class Item, template <class> class Array>
    template <class Func>
    bool
    ArrayList<Item, Array>::contains(const Item& item, Func&& func) const
    {
        ArrayListForwIter iter = {*this};

        return indexOf(item, iter, func) < m_count;
    }

    template <class Item, template <class> class Array>
    bool
    ArrayList<Item, Array>::contains(const Item& item) const
    {
        auto func = [](const Item& a, const Item& b) {
            return a == b;
        };

        return contains(item, func);
    }

    template <class Item, template <class> class Array>
    template <class Iter, class Func>
    void
    ArrayList<Item, Array>::forEach(Iter& iter, Func&& func) const
    {
        while ( iter.next() )
            func(iter.item(), iter.index(), m_count);
    }

    template <class Item, template <class> class Array>
    template <class Func>
    void
    ArrayList<Item, Array>::forEach(Func&& func) const
    {
        ArrayListForwIter iter = {*this};

        while ( iter.next() )
            func(iter.item(), iter.index(), m_count);
    }

    template <class Item, template <class> class Array>
    bool
    ArrayList<Item, Array>::resize(u32 size)
    {
        return m_array.resize(size);
    }

    template <class Item, template <class> class Array>
    bool
    ArrayList<Item, Array>::insert(const Item& item, u32 index)
    {
        if ( isFull() == false ) {
            if ( index > m_count ) index = m_count;

            for ( u32 i = m_count; i > index; i-- )
                m_array[i] = move(m_array[i - 1u]);

            ctor(m_array[index], item);
            m_count += 1u;

            return true;
        }

        return false;
    }

    template <class Item, template <class> class Array>
    bool
    ArrayList<Item, Array>::remove(u32 index)
    {
        if ( isEmpty() == false ) {
            m_count -= 1u;

            if ( index > m_count ) index = m_count;

            for ( u32 i = index; i < m_count; i++ )
                m_array[i] = move(m_array[i + 1u]);

            return true;
        }

        return false;
    }

    template <class Item, template <class> class Array>
    template <class Iter, class Func>
    void
    ArrayList<Item, Array>::clear(Iter& iter, Func&& func)
    {
        while ( iter.next() )
            func(iter.item(), iter.index(), m_count);

        m_count = 0;
    }

    template <class Item, template <class> class Array>
    template <class Func>
    void
    ArrayList<Item, Array>::clear(Func&& func)
    {
        ArrayListForwIter iter = {*this};

        while ( iter.next() )
            func(iter.item(), iter.index(), m_count);

        m_count = 0;
    }

    template <class Item, template <class> class Array>
    void
    ArrayList<Item, Array>::clear()
    {
        m_count = 0;
    }

    template <class Item, template <class> class Array>
    Item*
    ArrayList<Item, Array>::search(u32 index) const
    {
        if ( index < m_count )
            return &m_array[index];

        return 0;
    }

    template <class Item, template <class> class Array>
    Item&
    ArrayList<Item, Array>::find(u32 index) const
    {
        return *search(index);
    }

    template <class Item, template <class> class Array>
    const Array<Item>&
    ArrayList<Item, Array>::array() const
    {
        return m_array;
    }

    template <class Item, template <class> class Array>
    Item&
    ArrayList<Item, Array>::operator[](u32 index) const
    {
        return *search(index);
    }

    template <class Item, template <class> class Array>
    ArrayListForwIter<Item, Array>::ArrayListForwIter(const List& list)
        : m_list {list}
        , m_index {g_max_u32}
    { }

    template <class Item, template <class> class Array>
    u32
    ArrayListForwIter<Item, Array>::index() const
    {
        return m_index;
    }

    template <class Item, template <class> class Array>
    Item&
    ArrayListForwIter<Item, Array>::item()
    {
        return m_list.find(m_index);
    }

    template <class Item, template <class> class Array>
    const Item&
    ArrayListForwIter<Item, Array>::item() const
    {
        return m_list.find(m_index);
    }

    template <class Item, template <class> class Array>
    bool
    ArrayListForwIter<Item, Array>::hasNext() const
    {
        u32 next = m_index + 1u;

        if ( next < m_list.count() )
            return true;

        return false;
    }

    template <class Item, template <class> class Array>
    bool
    ArrayListForwIter<Item, Array>::next()
    {
        u32 next = m_index + 1u;

        if ( next < m_list.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, template <class> class Array>
    void
    ArrayListForwIter<Item, Array>::reset()
    {
        m_index = g_max_u32;
    }

    template <class Item, template <class> class Array>
    ArrayListBackIter<Item, Array>::ArrayListBackIter(const List& list)
        : m_list {list}
        , m_index {g_max_u32}
    { }

    template <class Item, template <class> class Array>
    u32
    ArrayListBackIter<Item, Array>::index() const
    {
        return m_index;
    }

    template <class Item, template <class> class Array>
    Item&
    ArrayListBackIter<Item, Array>::item()
    {
        u32 index = m_list.count() -
                    m_index;

        return m_list.find(index - 1u);
    }

    template <class Item, template <class> class Array>
    const Item&
    ArrayListBackIter<Item, Array>::item() const
    {
        u32 index = m_list.count() -
                    m_index;

        return m_list.find(index - 1u);
    }

    template <class Item, template <class> class Array>
    bool
    ArrayListBackIter<Item, Array>::hasNext() const
    {
        u32 next = m_index + 1u;

        if ( next < m_list.count() )
            return true;

        return false;
    }

    template <class Item, template <class> class Array>
    bool
    ArrayListBackIter<Item, Array>::next()
    {
        u32 next = m_index + 1u;

        if ( next < m_list.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, template <class> class Array>
    void
    ArrayListBackIter<Item, Array>::reset()
    {
        m_index = g_max_u32;
    }
} // namespace ma
