#include <smal/Algo/ArrayStack.hpp>

namespace ma
{
    template <class Item, template <class> class Array>
    ArrayStack<Item, Array>::ArrayStack()
        : m_array {}
        , m_count {0}
    { }

    template <class Item, template <class> class Array>
    ArrayStack<Item, Array>::ArrayStack(Array<Item>&& array)
        : m_array {move(array)}
        , m_count {0}
    { }

    template <class Item, template <class> class Array>
    template <class... Args>
    ArrayStack<Item, Array>::ArrayStack(BaseOrigin& origin, u32 size, Args&&... args)
        : m_array {origin, size, forw<Args>(args)...}
        , m_count {0}
    { }

    template <class Item, template <class> class Array>
    u32
    ArrayStack<Item, Array>::size() const
    {
        return m_array.size();
    }

    template <class Item, template <class> class Array>
    u32
    ArrayStack<Item, Array>::count() const
    {
        return m_count;
    }

    template <class Item, template <class> class Array>
    bool
    ArrayStack<Item, Array>::isEmpty() const
    {
        return m_count == 0;
    }

    template <class Item, template <class> class Array>
    bool
    ArrayStack<Item, Array>::isFull() const
    {
        return m_count == size();
    }

    template <class Item, template <class> class Array>
    template <class Iter, class Func>
    u32
    ArrayStack<Item, Array>::indexOf(const Item& item, Iter& iter, Func&& func) const
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
    ArrayStack<Item, Array>::indexOf(const Item& item, Func&& func) const
    {
        ArrayStackForwIter iter = {*this};

        while ( iter.next() ) {
            if ( func(iter.item(), item) == true )
                return iter.index();
        }

        return g_max_u32;
    }

    template <class Item, template <class> class Array>
    u32
    ArrayStack<Item, Array>::indexOf(const Item& item) const
    {
        auto func = [](const Item& a, const Item& b) {
            return a == b;
        };

        return indexOf(item, func);
    }

    template <class Item, template <class> class Array>
    template <class Iter, class Func>
    bool
    ArrayStack<Item, Array>::contains(const Item& item, Iter& iter, Func&& func) const
    {
        return indexOf(item, iter, func) < m_count;
    }

    template <class Item, template <class> class Array>
    template <class Func>
    bool
    ArrayStack<Item, Array>::contains(const Item& item, Func&& func) const
    {
        ArrayStackForwIter iter = {*this};

        return indexOf(item, iter, func) < m_count;
    }

    template <class Item, template <class> class Array>
    bool
    ArrayStack<Item, Array>::contains(const Item& item) const
    {
        auto func = [](const Item& a, const Item& b) {
            return a == b;
        };

        return contains(item, func);
    }

    template <class Item, template <class> class Array>
    template <class Iter, class Func>
    void
    ArrayStack<Item, Array>::forEach(Iter& iter, Func&& func) const
    {
        while ( iter.next() )
            func(iter.index(), iter.item(), m_count);
    }

    template <class Item, template <class> class Array>
    template <class Func>
    void
    ArrayStack<Item, Array>::forEach(Func&& func) const
    {
        ArrayStackForwIter iter = {*this};

        while ( iter.next() )
            func(iter.index(), iter.item(), m_count);
    }

    template <class Item, template <class> class Array>
    bool
    ArrayStack<Item, Array>::resize(u32 size)
    {
        return m_array.resize(size);
    }

    template <class Item, template <class> class Array>
    bool
    ArrayStack<Item, Array>::insert(const Item& item)
    {
        if ( isFull() == false ) {
            ctor(m_array[m_count], item);
            m_count += 1u;

            return true;
        }

        return false;
    }

    template <class Item, template <class> class Array>
    bool
    ArrayStack<Item, Array>::remove()
    {
        if ( isEmpty() == false ) {
            m_count -= 1u;

            return true;
        }

        return false;
    }

    template <class Item, template <class> class Array>
    template <class Iter, class Func>
    void
    ArrayStack<Item, Array>::clear(Iter& iter, Func&& func)
    {
        while ( iter.next() )
            func(iter.index(), iter.item(), m_count);

        m_count = 0;
    }

    template <class Item, template <class> class Array>
    template <class Func>
    void
    ArrayStack<Item, Array>::clear(Func&& func)
    {
        ArrayStackForwIter iter = {*this};

        while ( iter.next() )
            func(iter.index(), iter.item(), m_count);

        m_count = 0;
    }

    template <class Item, template <class> class Array>
    void
    ArrayStack<Item, Array>::clear()
    {
        m_count = 0;
    }

    template <class Item, template <class> class Array>
    Item&
    ArrayStack<Item, Array>::find(u32 index, Item& deflt) const
    {
        if ( index < m_count )
            return m_array[index];

        return deflt;
    }

    template <class Item, template <class> class Array>
    Item&
    ArrayStack<Item, Array>::find(u32 index) const
    {
        return m_array[index];
    }

    template <class Item, template <class> class Array>
    const Array<Item>&
    ArrayStack<Item, Array>::array() const
    {
        return m_array;
    }

    template <class Item, template <class> class Array>
    Item&
    ArrayStack<Item, Array>::operator[](u32 index) const
    {
        return find(index);
    }

    template <class Item, template <class> class Array>
    ArrayStackForwIter<Item, Array>::ArrayStackForwIter(const Stack& stack)
        : m_stack {stack}
        , m_index {g_max_u32}
    { }

    template <class Item, template <class> class Array>
    u32
    ArrayStackForwIter<Item, Array>::index() const
    {
        return m_index;
    }

    template <class Item, template <class> class Array>
    Item&
    ArrayStackForwIter<Item, Array>::item()
    {
        return m_stack.find(m_index);
    }

    template <class Item, template <class> class Array>
    const Item&
    ArrayStackForwIter<Item, Array>::item() const
    {
        return m_stack.find(m_index);
    }

    template <class Item, template <class> class Array>
    bool
    ArrayStackForwIter<Item, Array>::hasNext() const
    {
        u32 next = m_index + 1u;

        if ( next < m_stack.count() )
            return true;

        return false;
    }

    template <class Item, template <class> class Array>
    bool
    ArrayStackForwIter<Item, Array>::next()
    {
        u32 next = m_index + 1u;

        if ( next < m_stack.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, template <class> class Array>
    void
    ArrayStackForwIter<Item, Array>::reset()
    {
        m_index = g_max_u32;
    }

    template <class Item, template <class> class Array>
    ArrayStackBackIter<Item, Array>::ArrayStackBackIter(const Stack& stack)
        : m_stack {stack}
        , m_index {g_max_u32}
    { }

    template <class Item, template <class> class Array>
    u32
    ArrayStackBackIter<Item, Array>::index() const
    {
        return m_index;
    }

    template <class Item, template <class> class Array>
    Item&
    ArrayStackBackIter<Item, Array>::item()
    {
        u32 index = m_stack.count() -
                    m_index;

        return m_stack.find(index - 1u);
    }

    template <class Item, template <class> class Array>
    const Item&
    ArrayStackBackIter<Item, Array>::item() const
    {
        u32 index = m_stack.count() -
                    m_index;

        return m_stack.find(index - 1u);
    }

    template <class Item, template <class> class Array>
    bool
    ArrayStackBackIter<Item, Array>::hasNext() const
    {
        u32 next = m_index + 1u;

        if ( next < m_stack.count() )
            return true;

        return false;
    }

    template <class Item, template <class> class Array>
    bool
    ArrayStackBackIter<Item, Array>::next()
    {
        u32 next = m_index + 1u;

        if ( next < m_stack.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, template <class> class Array>
    void
    ArrayStackBackIter<Item, Array>::reset()
    {
        m_index = g_max_u32;
    }
} // namespace ma
