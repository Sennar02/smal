#include <smal/Algo/ArrayList.hpp>

namespace ma
{
    template <class Item, template <class> class Block>
    ArrayList<Item, Block>::ArrayList()
        : m_block {}
        , m_count {0}
    { }

    template <class Item, template <class> class Block>
    ArrayList<Item, Block>::ArrayList(const Block<Item>& block, u32 count)
        : m_block {block}
        , m_count {0}
    {
        if ( count > m_block.size() )
            count = m_block.size();

        m_count = count;
    }

    template <class Item, template <class> class Block>
    template <class Alloc>
    ArrayList<Item, Block>::ArrayList(Alloc& alloc, u32 size, u32 count)
        : ArrayList({alloc, size}, count)
    { }

    template <class Item, template <class> class Block>
    u32
    ArrayList<Item, Block>::size() const
    {
        return m_block.size();
    }

    template <class Item, template <class> class Block>
    u32
    ArrayList<Item, Block>::count() const
    {
        return m_count;
    }

    template <class Item, template <class> class Block>
    bool
    ArrayList<Item, Block>::isEmpty() const
    {
        return m_count == 0;
    }

    template <class Item, template <class> class Block>
    bool
    ArrayList<Item, Block>::isFull() const
    {
        return m_count == size();
    }

    template <class Item, template <class> class Block>
    template <class Iter, class Func>
    u32
    ArrayList<Item, Block>::indexOf(const Item& item, Iter& iter, Func&& func) const
    {
        while ( true ) {
            if ( func(iter.item(), item) == true )
                return iter.index();

            if ( iter.next() == false )
                break;
        }

        return g_max_u32;
    }

    template <class Item, template <class> class Block>
    template <class Func>
    u32
    ArrayList<Item, Block>::indexOf(const Item& item, Func&& func) const
    {
        ArrayListForwIter iter =
            {*this};

        return indexOf(item, iter, func);
    }

    template <class Item, template <class> class Block>
    u32
    ArrayList<Item, Block>::indexOf(const Item& item) const
    {
        auto func = [](const Item& a, const Item& b) {
            return a == b;
        };

        return indexOf(item, func);
    }

    template <class Item, template <class> class Block>
    template <class Iter, class Func>
    bool
    ArrayList<Item, Block>::contains(const Item& item, Iter& iter, Func&& func) const
    {
        return indexOf(item, iter, func) < m_count;
    }

    template <class Item, template <class> class Block>
    template <class Func>
    bool
    ArrayList<Item, Block>::contains(const Item& item, Func&& func) const
    {
        ArrayListForwIter iter =
            {*this};

        return contains(item, iter, func);
    }

    template <class Item, template <class> class Block>
    bool
    ArrayList<Item, Block>::contains(const Item& item) const
    {
        auto func = [](const Item& a, const Item& b) {
            return a == b;
        };

        return contains(item, func);
    }

    template <class Item, template <class> class Block>
    template <class Iter, class Func>
    void
    ArrayList<Item, Block>::forEach(Iter& iter, Func&& func) const
    {
        while ( true ) {
            func(iter.item(), iter.index(), m_count);

            if ( iter.next() == false )
                break;
        }
    }

    template <class Item, template <class> class Block>
    template <class Func>
    void
    ArrayList<Item, Block>::forEach(Func&& func) const
    {
        ArrayListForwIter iter =
            {*this};

        forEach(iter, func);
    }

    template <class Item, template <class> class Block>
    bool
    ArrayList<Item, Block>::resize(u32 size)
    {
        return m_block.resize(size);
    }

    template <class Item, template <class> class Block>
    bool
    ArrayList<Item, Block>::insert(const Item& item, u32 index)
    {
        if ( isFull() == false ) {
            if ( index > m_count ) index = m_count;

            for ( u32 i = m_count; i > index; i-- )
                m_block[i] = move(m_block[i - 1]);

            m_block[index] = item;
            m_count += 1;

            return true;
        }

        return false;
    }

    template <class Item, template <class> class Block>
    bool
    ArrayList<Item, Block>::remove(u32 index)
    {
        if ( isEmpty() == false ) {
            m_count -= 1;

            if ( index > m_count ) index = m_count;

            for ( u32 i = index; i < m_count; i++ )
                m_block[i] = move(m_block[i + 1]);

            return true;
        }

        return false;
    }

    template <class Item, template <class> class Block>
    template <class Iter, class Func>
    void
    ArrayList<Item, Block>::clear(Iter& iter, Func&& func)
    {
        while ( true ) {
            func(iter.item(), iter.index(), m_count);

            if ( iter.next() == false )
                break;
        }

        resize(0);
    }

    template <class Item, template <class> class Block>
    template <class Func>
    void
    ArrayList<Item, Block>::clear(Func&& func)
    {
        ArrayListForwIter iter =
            {*this};

        clear(iter, func);
    }

    template <class Item, template <class> class Block>
    Item*
    ArrayList<Item, Block>::search(u32 index) const
    {
        if ( index < m_count )
            return &m_block[index];

        return 0;
    }

    template <class Item, template <class> class Block>
    Item&
    ArrayList<Item, Block>::find(u32 index) const
    {
        return *search(index);
    }

    template <class Item, template <class> class Block>
    const Block<Item>&
    ArrayList<Item, Block>::block() const
    {
        return m_block;
    }

    template <class Item, template <class> class Block>
    Item&
    ArrayList<Item, Block>::operator[](u32 index) const
    {
        return find(index);
    }

    template <class Item, template <class> class Block>
    ArrayListForwIter<Item, Block>::ArrayListForwIter(const List& list, u32 start)
        : m_list {list}
        , m_index {0}
    {
        clear(start);
    }

    template <class Item, template <class> class Block>
    u32
    ArrayListForwIter<Item, Block>::index() const
    {
        return m_index;
    }

    template <class Item, template <class> class Block>
    Item&
    ArrayListForwIter<Item, Block>::item()
    {
        return m_list.find(m_index);
    }

    template <class Item, template <class> class Block>
    const Item&
    ArrayListForwIter<Item, Block>::item() const
    {
        return m_list.find(m_index);
    }

    template <class Item, template <class> class Block>
    bool
    ArrayListForwIter<Item, Block>::hasNext() const
    {
        u32 next = m_index + 1;

        if ( next < m_list.count() )
            return true;

        return false;
    }

    template <class Item, template <class> class Block>
    bool
    ArrayListForwIter<Item, Block>::next()
    {
        u32 next = m_index + 1;

        if ( next < m_list.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, template <class> class Block>
    void
    ArrayListForwIter<Item, Block>::clear(u32 start)
    {
        u32 count = m_list.count() - 1;

        if ( start > count )
            start = count;

        m_index = start;
    }

    template <class Item, template <class> class Block>
    ArrayListBackIter<Item, Block>::ArrayListBackIter(const List& list, u32 start)
        : m_list {list}
        , m_index {0}
    {
        clear(start);
    }

    template <class Item, template <class> class Block>
    u32
    ArrayListBackIter<Item, Block>::index() const
    {
        return m_index;
    }

    template <class Item, template <class> class Block>
    Item&
    ArrayListBackIter<Item, Block>::item()
    {
        u32 index = m_list.count() -
                    m_index;

        return m_list.find(index - 1);
    }

    template <class Item, template <class> class Block>
    const Item&
    ArrayListBackIter<Item, Block>::item() const
    {
        u32 index = m_list.count() -
                    m_index;

        return m_list.find(index - 1);
    }

    template <class Item, template <class> class Block>
    bool
    ArrayListBackIter<Item, Block>::hasNext() const
    {
        u32 next = m_index + 1;

        if ( next < m_list.count() )
            return true;

        return false;
    }

    template <class Item, template <class> class Block>
    bool
    ArrayListBackIter<Item, Block>::next()
    {
        u32 next = m_index + 1;

        if ( next < m_list.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, template <class> class Block>
    void
    ArrayListBackIter<Item, Block>::clear(u32 start)
    {
        u32 count = m_list.count() - 1;

        if ( start > count )
            start = count;

        m_index = start;
    }
} // namespace ma
