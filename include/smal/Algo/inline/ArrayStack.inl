#include <smal/Algo/ArrayStack.hpp>

namespace ma
{
    template <class Item, class Layout>
    ArrayStack<Item, Layout>::ArrayStack()
        : m_array {}
        , m_count {0}
    { }

    template <class Item, class Layout>
    ArrayStack<Item, Layout>::ArrayStack(const Layout& array)
        : m_array {array}
        , m_count {0}
    { }

    template <class Item, class Layout>
    template <class... Args>
    ArrayStack<Item, Layout>::ArrayStack(Args&&... args)
        : m_array {forw<Args>(args)...}
        , m_count {0}
    { }

    template <class Item, class Layout>
    u32
    ArrayStack<Item, Layout>::size() const
    {
        return m_array.length();
    }

    template <class Item, class Layout>
    u32
    ArrayStack<Item, Layout>::count() const
    {
        return m_count;
    }

    template <class Item, class Layout>
    bool
    ArrayStack<Item, Layout>::isEmpty() const
    {
        return m_count == 0;
    }

    template <class Item, class Layout>
    bool
    ArrayStack<Item, Layout>::isFull() const
    {
        return m_count == m_array.length();
    }

    template <class Item, class Layout>
    template <class Iter, class Func>
    u32
    ArrayStack<Item, Layout>::indexOf(const Item& item, Iter& iter, Func&& func) const
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
    ArrayStack<Item, Layout>::indexOf(const Item& item, Func&& func) const
    {
        ArrayStackForwIter iter = {*this};

        while ( iter.next() ) {
            if ( func(iter.item(), item) == true )
                return iter.index();
        }

        return g_max_u32;
    }

    template <class Item, class Layout>
    u32
    ArrayStack<Item, Layout>::indexOf(const Item& item) const
    {
        auto func = [](const Item& a, const Item& b) {
            return a == b;
        };

        return indexOf(item, func);
    }

    template <class Item, class Layout>
    template <class Iter, class Func>
    bool
    ArrayStack<Item, Layout>::contains(const Item& item, Iter& iter, Func&& func) const
    {
        return indexOf(item, iter, func) < m_count;
    }

    template <class Item, class Layout>
    template <class Func>
    bool
    ArrayStack<Item, Layout>::contains(const Item& item, Func&& func) const
    {
        ArrayStackForwIter iter = {*this};

        return indexOf(item, iter, func) < m_count;
    }

    template <class Item, class Layout>
    bool
    ArrayStack<Item, Layout>::contains(const Item& item) const
    {
        auto func = [](const Item& a, const Item& b) {
            return a == b;
        };

        return contains(item, func);
    }

    template <class Item, class Layout>
    template <class Iter, class Func>
    void
    ArrayStack<Item, Layout>::forEach(Iter& iter, Func&& func) const
    {
        while ( iter.next() )
            func(iter.item(), iter.index());
    }

    template <class Item, class Layout>
    template <class Func>
    void
    ArrayStack<Item, Layout>::forEach(Func&& func) const
    {
        ArrayStackForwIter iter = {*this};

        while ( iter.next() )
            func(iter.item(), iter.index());
    }

    template <class Item, class Layout>
    bool
    ArrayStack<Item, Layout>::resize(u32 size)
    {
        return m_array.resize(size);
    }

    template <class Item, class Layout>
    bool
    ArrayStack<Item, Layout>::insert(const Item& item)
    {
        bool flag = isFull();

        if ( flag == false )
            ctor(m_array[m_count++], item);

        return flag == false;
    }

    template <class Item, class Layout>
    bool
    ArrayStack<Item, Layout>::remove()
    {
        bool flag = isFull();

        if ( flag == false )
            m_count -= 1u;

        return flag == false;
    }

    template <class Item, class Layout>
    template <class Iter, class Func>
    void
    ArrayStack<Item, Layout>::clear(Iter& iter, Func&& func)
    {
        while ( iter.next() )
            func(iter.item(), iter.index());

        m_count = 0;
    }

    template <class Item, class Layout>
    template <class Func>
    void
    ArrayStack<Item, Layout>::clear(Func&& func)
    {
        ArrayStackForwIter iter = {*this};

        while ( iter.next() )
            func(iter.item(), iter.index());

        m_count = 0;
    }

    template <class Item, class Layout>
    void
    ArrayStack<Item, Layout>::clear()
    {
        m_count = 0;
    }

    template <class Item, class Layout>
    Item&
    ArrayStack<Item, Layout>::find(u32 index, Item& deflt) const
    {
        if ( index < m_count )
            return m_array[index];

        return deflt;
    }

    template <class Item, class Layout>
    Item&
    ArrayStack<Item, Layout>::find(u32 index) const
    {
        return m_array[index];
    }

    template <class Item, class Layout>
    const Array<Item, Layout>&
    ArrayStack<Item, Layout>::array() const
    {
        return m_array;
    }

    template <class Item, class Layout>
    Item&
    ArrayStack<Item, Layout>::operator[](u32 index) const
    {
        return m_array[index];
    }

    template <class Item, class Layout>
    ArrayStackForwIter<Item, Layout>::ArrayStackForwIter(const Stack& stack)
        : m_stack {stack}
        , m_index {g_max_u32}
    { }

    template <class Item, class Layout>
    u32
    ArrayStackForwIter<Item, Layout>::index() const
    {
        return m_index;
    }

    template <class Item, class Layout>
    Item&
    ArrayStackForwIter<Item, Layout>::item()
    {
        return m_stack.array()[m_index];
    }

    template <class Item, class Layout>
    const Item&
    ArrayStackForwIter<Item, Layout>::item() const
    {
        return m_stack.array()[m_index];
    }

    template <class Item, class Layout>
    bool
    ArrayStackForwIter<Item, Layout>::hasNext() const
    {
        u32 next = m_index + 1u;

        if ( next < m_stack.count() )
            return true;

        return false;
    }

    template <class Item, class Layout>
    bool
    ArrayStackForwIter<Item, Layout>::next()
    {
        u32 next = m_index + 1u;

        if ( next < m_stack.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, class Layout>
    void
    ArrayStackForwIter<Item, Layout>::reset()
    {
        m_index = g_max_u32;
    }

    template <class Item, class Layout>
    ArrayStackBackIter<Item, Layout>::ArrayStackBackIter(const Stack& stack)
        : m_stack {stack}
        , m_index {g_max_u32}
    { }

    template <class Item, class Layout>
    u32
    ArrayStackBackIter<Item, Layout>::index() const
    {
        return m_index;
    }

    template <class Item, class Layout>
    Item&
    ArrayStackBackIter<Item, Layout>::item()
    {
        u32 index = m_stack.count() -
                    m_index - 1u;

        return m_stack.array()[index];
    }

    template <class Item, class Layout>
    const Item&
    ArrayStackBackIter<Item, Layout>::item() const
    {
        u32 index = m_stack.count() -
                    m_index - 1u;

        return m_stack.array()[index];
    }

    template <class Item, class Layout>
    bool
    ArrayStackBackIter<Item, Layout>::hasNext() const
    {
        u32 next = m_index + 1u;

        if ( next < m_stack.count() )
            return true;

        return false;
    }

    template <class Item, class Layout>
    bool
    ArrayStackBackIter<Item, Layout>::next()
    {
        u32 next = m_index + 1u;

        if ( next < m_stack.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, class Layout>
    void
    ArrayStackBackIter<Item, Layout>::reset()
    {
        m_index = g_max_u32;
    }
} // namespace ma
