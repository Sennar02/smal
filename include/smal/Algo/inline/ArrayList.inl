#include <smal/Algo/ArrayList.hpp>

namespace ma
{
    template <class Item, template <class> class Buffer>
    ArrayList<Item, Buffer>::ArrayList()
        : m_array {}
        , m_count {0}
    { }

    template <class Item, template <class> class Buffer>
    template <class... Args>
    ArrayList<Item, Buffer>::ArrayList(Args&&... args)
        : m_array {forw<Args>(args)...}
        , m_count {0}
    { }

    template <class Item, template <class> class Buffer>
    u32
    ArrayList<Item, Buffer>::size() const
    {
        return m_array.size();
    }

    template <class Item, template <class> class Buffer>
    u32
    ArrayList<Item, Buffer>::count() const
    {
        return m_count;
    }

    template <class Item, template <class> class Buffer>
    bool
    ArrayList<Item, Buffer>::isEmpty() const
    {
        return m_count == 0;
    }

    template <class Item, template <class> class Buffer>
    bool
    ArrayList<Item, Buffer>::isFull() const
    {
        return m_count == size();
    }

    template <class Item, template <class> class Buffer>
    template <class Iter, class Func>
    u32
    ArrayList<Item, Buffer>::indexOf(const Item& item, Iter& iter, Func&& func) const
    {
        while ( iter.next() ) {
            if ( func(iter.item(), item) == true )
                return iter.index();
        }

        return g_max_u32;
    }

    template <class Item, template <class> class Buffer>
    template <class Func>
    u32
    ArrayList<Item, Buffer>::indexOf(const Item& item, Func&& func) const
    {
        ArrayListForwIter iter = {*this};

        while ( iter.next() ) {
            if ( func(iter.item(), item) == true )
                return iter.index();
        }

        return g_max_u32;
    }

    template <class Item, template <class> class Buffer>
    u32
    ArrayList<Item, Buffer>::indexOf(const Item& item) const
    {
        auto func = [](const Item& a, const Item& b) {
            return a == b;
        };

        return indexOf(item, func);
    }

    template <class Item, template <class> class Buffer>
    template <class Iter, class Func>
    bool
    ArrayList<Item, Buffer>::contains(const Item& item, Iter& iter, Func&& func) const
    {
        return indexOf(item, iter, func) < m_count;
    }

    template <class Item, template <class> class Buffer>
    template <class Func>
    bool
    ArrayList<Item, Buffer>::contains(const Item& item, Func&& func) const
    {
        ArrayListForwIter iter = {*this};

        return indexOf(item, iter, func) < m_count;
    }

    template <class Item, template <class> class Buffer>
    bool
    ArrayList<Item, Buffer>::contains(const Item& item) const
    {
        auto func = [](const Item& a, const Item& b) {
            return a == b;
        };

        return contains(item, func);
    }

    template <class Item, template <class> class Buffer>
    template <class Iter, class Func>
    void
    ArrayList<Item, Buffer>::forEach(Iter& iter, Func&& func) const
    {
        while ( iter.next() )
            func(iter.item(), iter.index(), m_count);
    }

    template <class Item, template <class> class Buffer>
    template <class Func>
    void
    ArrayList<Item, Buffer>::forEach(Func&& func) const
    {
        ArrayListForwIter iter = {*this};

        while ( iter.next() )
            func(iter.item(), iter.index(), m_count);
    }

    template <class Item, template <class> class Buffer>
    bool
    ArrayList<Item, Buffer>::resize(u32 size)
    {
        return m_array.resize(size);
    }

    template <class Item, template <class> class Buffer>
    bool
    ArrayList<Item, Buffer>::insert(const Item& item, u32 index)
    {
        if ( isFull() == false ) {
            if ( index > m_count ) index = m_count;

            for ( u32 i = m_count; i > index; i-- )
                m_array[i] = move(m_array[i - 1]);

            ctor(m_array[index], item);
            m_count += 1;

            return true;
        }

        return false;
    }

    template <class Item, template <class> class Buffer>
    bool
    ArrayList<Item, Buffer>::remove(u32 index)
    {
        if ( isEmpty() == false ) {
            m_count -= 1;

            if ( index > m_count ) index = m_count;

            for ( u32 i = index; i < m_count; i++ )
                m_array[i] = move(m_array[i + 1]);

            return true;
        }

        return false;
    }

    template <class Item, template <class> class Buffer>
    template <class Iter, class Func>
    void
    ArrayList<Item, Buffer>::clear(Iter& iter, Func&& func)
    {
        while ( iter.next() )
            func(iter.item(), iter.index(), m_count);

        m_count = 0;
    }

    template <class Item, template <class> class Buffer>
    template <class Func>
    void
    ArrayList<Item, Buffer>::clear(Func&& func)
    {
        ArrayListForwIter iter = {*this};

        while ( iter.next() )
            func(iter.item(), iter.index(), m_count);

        m_count = 0;
    }

    template <class Item, template <class> class Buffer>
    void
    ArrayList<Item, Buffer>::clear()
    {
        m_count = 0;
    }

    template <class Item, template <class> class Buffer>
    Item*
    ArrayList<Item, Buffer>::search(u32 index) const
    {
        if ( index < m_count )
            return &m_array[index];

        return 0;
    }

    template <class Item, template <class> class Buffer>
    Item&
    ArrayList<Item, Buffer>::find(u32 index) const
    {
        return *search(index);
    }

    template <class Item, template <class> class Buffer>
    const Buffer<Item>&
    ArrayList<Item, Buffer>::buffer() const
    {
        return m_array;
    }

    template <class Item, template <class> class Buffer>
    Item&
    ArrayList<Item, Buffer>::operator[](u32 index) const
    {
        return *search(index);
    }

    template <class Item, template <class> class Buffer>
    ArrayListForwIter<Item, Buffer>::ArrayListForwIter(const List& list)
        : m_list {list}
        , m_index {g_max_u32}
    { }

    template <class Item, template <class> class Buffer>
    u32
    ArrayListForwIter<Item, Buffer>::index() const
    {
        return m_index;
    }

    template <class Item, template <class> class Buffer>
    Item&
    ArrayListForwIter<Item, Buffer>::item()
    {
        return m_list.find(m_index);
    }

    template <class Item, template <class> class Buffer>
    const Item&
    ArrayListForwIter<Item, Buffer>::item() const
    {
        return m_list.find(m_index);
    }

    template <class Item, template <class> class Buffer>
    bool
    ArrayListForwIter<Item, Buffer>::hasNext() const
    {
        u32 next = m_index + 1;

        if ( next < m_list.count() )
            return true;

        return false;
    }

    template <class Item, template <class> class Buffer>
    bool
    ArrayListForwIter<Item, Buffer>::next()
    {
        u32 next = m_index + 1;

        if ( next < m_list.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, template <class> class Buffer>
    void
    ArrayListForwIter<Item, Buffer>::reset()
    {
        m_index = g_max_u32;
    }

    template <class Item, template <class> class Buffer>
    ArrayListBackIter<Item, Buffer>::ArrayListBackIter(const List& list)
        : m_list {list}
        , m_index {g_max_u32}
    { }

    template <class Item, template <class> class Buffer>
    u32
    ArrayListBackIter<Item, Buffer>::index() const
    {
        return m_index;
    }

    template <class Item, template <class> class Buffer>
    Item&
    ArrayListBackIter<Item, Buffer>::item()
    {
        u32 index = m_list.count() -
                    m_index;

        return m_list.find(index - 1);
    }

    template <class Item, template <class> class Buffer>
    const Item&
    ArrayListBackIter<Item, Buffer>::item() const
    {
        u32 index = m_list.count() -
                    m_index;

        return m_list.find(index - 1);
    }

    template <class Item, template <class> class Buffer>
    bool
    ArrayListBackIter<Item, Buffer>::hasNext() const
    {
        u32 next = m_index + 1;

        if ( next < m_list.count() )
            return true;

        return false;
    }

    template <class Item, template <class> class Buffer>
    bool
    ArrayListBackIter<Item, Buffer>::next()
    {
        u32 next = m_index + 1;

        if ( next < m_list.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, template <class> class Buffer>
    void
    ArrayListBackIter<Item, Buffer>::reset()
    {
        m_index = g_max_u32;
    }
} // namespace ma
