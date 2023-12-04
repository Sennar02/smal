#include <smal/Algo/ArrayList.hpp>

namespace ma
{
    template <class Type, template <class> class Block>
    ArrayList<Type, Block>::ArrayList()
        : m_block {}
        , m_count {0}
    { }

    template <class Type, template <class> class Block>
    ArrayList<Type, Block>::ArrayList(const Block<Type>& block, u32 count)
        : m_block {block}
        , m_count {0}
    {
        if ( count > m_block.size() )
            count = m_block.size();

        m_count = count;
    }

    template <class Type, template <class> class Block>
    template <class Alloc>
    ArrayList<Type, Block>::ArrayList(Alloc& alloc, u32 size, u32 count)
        : ArrayList({alloc, size}, count)
    { }

    template <class Type, template <class> class Block>
    u32
    ArrayList<Type, Block>::size() const
    {
        return m_block.size();
    }

    template <class Type, template <class> class Block>
    u32
    ArrayList<Type, Block>::count() const
    {
        return m_count;
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::isEmpty() const
    {
        return m_count == 0;
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::isFull() const
    {
        return m_count == size();
    }

    template <class Type, template <class> class Block>
    template <class Iter, class Func>
    u32
    ArrayList<Type, Block>::indexOf(const Type& value, Iter& iter, Func&& func) const
    {
        while ( true ) {
            if ( func(iter.item(), value) == true )
                return iter.index();

            if ( iter.next() == false )
                break;
        }

        return g_max_u32;
    }

    template <class Type, template <class> class Block>
    template <class Func>
    u32
    ArrayList<Type, Block>::indexOf(const Type& value, Func&& func) const
    {
        ArrayListForwIter iter =
            {*this};

        return indexOf(value, iter, func);
    }

    template <class Type, template <class> class Block>
    u32
    ArrayList<Type, Block>::indexOf(const Type& value) const
    {
        auto func = [](const Type& a, const Type& b) {
            return a == b;
        };

        return indexOf(value, func);
    }

    template <class Type, template <class> class Block>
    template <class Iter, class Func>
    bool
    ArrayList<Type, Block>::contains(const Type& value, Iter& iter, Func&& func) const
    {
        return indexOf(value, iter, func) < m_count;
    }

    template <class Type, template <class> class Block>
    template <class Func>
    bool
    ArrayList<Type, Block>::contains(const Type& value, Func&& func) const
    {
        ArrayListForwIter iter =
            {*this};

        return contains(value, iter, func);
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::contains(const Type& value) const
    {
        auto func = [](const Type& a, const Type& b) {
            return a == b;
        };

        return contains(value, func);
    }

    template <class Type, template <class> class Block>
    template <class Iter, class Func>
    void
    ArrayList<Type, Block>::forEach(Iter& iter, Func&& func) const
    {
        while ( true ) {
            func(iter.item(), iter.index(), m_count);

            if ( iter.next() == false )
                break;
        }
    }

    template <class Type, template <class> class Block>
    template <class Func>
    void
    ArrayList<Type, Block>::forEach(Func&& func) const
    {
        ArrayListForwIter iter =
            {*this};

        forEach(iter, func);
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::resize(u32 size)
    {
        return m_block.resize(size);
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::insert(const Type& value, u32 index)
    {
        if ( isFull() == false ) {
            if ( index > m_count ) index = m_count;

            for ( u32 i = m_count; i > index; i-- )
                m_block[i] = move(m_block[i - 1]);

            m_block[index] = value;
            m_count += 1;

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::remove(u32 index)
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

    template <class Type, template <class> class Block>
    template <class Iter, class Func>
    void
    ArrayList<Type, Block>::clear(Iter& iter, Func&& func)
    {
        while ( true ) {
            func(iter.item(), iter.index(), m_count);

            if ( iter.next() == false )
                break;
        }

        resize(0);
    }

    template <class Type, template <class> class Block>
    template <class Func>
    void
    ArrayList<Type, Block>::clear(Func&& func)
    {
        ArrayListForwIter iter =
            {*this};

        clear(iter, func);
    }

    template <class Type, template <class> class Block>
    Type&
    ArrayList<Type, Block>::find(u32 index) const
    {
        return m_block[index];
    }

    template <class Type, template <class> class Block>
    const Block<Type>&
    ArrayList<Type, Block>::block() const
    {
        return m_block;
    }

    template <class Type, template <class> class Block>
    Type&
    ArrayList<Type, Block>::operator[](u32 index) const
    {
        return find(index);
    }

    template <class Type, template <class> class Block>
    ArrayListForwIter<Type, Block>::ArrayListForwIter(const List& list, u32 start)
        : m_list {list}
        , m_index {0}
    {
        clear(start);
    }

    template <class Type, template <class> class Block>
    u32
    ArrayListForwIter<Type, Block>::index() const
    {
        return m_index;
    }

    template <class Type, template <class> class Block>
    Type&
    ArrayListForwIter<Type, Block>::item()
    {
        return m_list.find(m_index);
    }

    template <class Type, template <class> class Block>
    const Type&
    ArrayListForwIter<Type, Block>::item() const
    {
        return m_list.find(m_index);
    }

    template <class Type, template <class> class Block>
    bool
    ArrayListForwIter<Type, Block>::hasNext() const
    {
        u32 next = m_index + 1;

        if ( next < m_list.count() )
            return true;

        return false;
    }

    template <class Type, template <class> class Block>
    bool
    ArrayListForwIter<Type, Block>::next()
    {
        u32 next = m_index + 1;

        if ( next < m_list.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Type, template <class> class Block>
    void
    ArrayListForwIter<Type, Block>::clear(u32 start)
    {
        u32 count = m_list.count() - 1;

        if ( start > count )
            start = count;

        m_index = start;
    }

    template <class Type, template <class> class Block>
    ArrayListBackIter<Type, Block>::ArrayListBackIter(const List& list, u32 start)
        : m_list {list}
        , m_index {0}
    {
        clear(start);
    }

    template <class Type, template <class> class Block>
    u32
    ArrayListBackIter<Type, Block>::index() const
    {
        return m_index;
    }

    template <class Type, template <class> class Block>
    Type&
    ArrayListBackIter<Type, Block>::item()
    {
        u32 index = m_list.count() -
                    m_index;

        return m_list.find(index - 1);
    }

    template <class Type, template <class> class Block>
    const Type&
    ArrayListBackIter<Type, Block>::item() const
    {
        u32 index = m_list.count() -
                    m_index;

        return m_list.find(index - 1);
    }

    template <class Type, template <class> class Block>
    bool
    ArrayListBackIter<Type, Block>::hasNext() const
    {
        u32 next = m_index + 1;

        if ( next < m_list.count() )
            return true;

        return false;
    }

    template <class Type, template <class> class Block>
    bool
    ArrayListBackIter<Type, Block>::next()
    {
        u32 next = m_index + 1;

        if ( next < m_list.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Type, template <class> class Block>
    void
    ArrayListBackIter<Type, Block>::clear(u32 start)
    {
        u32 count = m_list.count() - 1;

        if ( start > count )
            start = count;

        m_index = start;
    }
} // namespace ma
