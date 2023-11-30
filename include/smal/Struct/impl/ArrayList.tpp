#include <smal/Struct/ArrayList.hpp>

namespace ma
{
    template <class Type, template <class> class Block>
    ArrayList<Type, Block>::ArrayList()
        : m_block {}
        , m_count {0}
    { }

    template <class Type, template <class> class Block>
    template <class Alloc>
    ArrayList<Type, Block>::ArrayList(const Alloc& alloc, usize size, usize count)
        : m_block {}
        , m_count {0}
    {
        m_block = {alloc, size};

        if ( count > m_block.size() )
            count = m_block.size();

        m_count = count;
    }

    template <class Type, template <class> class Block>
    ArrayList<Type, Block>::ArrayList(const Block<Type>& block, usize count)
        : m_block {block}
        , m_count {0}
    {
        if ( count > m_block.size() )
            count = m_block.size();

        m_count = count;
    }

    template <class Type, template <class> class Block>
    usize
    ArrayList<Type, Block>::size() const
    {
        return m_block.size();
    }

    template <class Type, template <class> class Block>
    usize
    ArrayList<Type, Block>::count() const
    {
        return m_count;
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::is_empty() const
    {
        return m_count == 0;
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::is_full() const
    {
        return m_count == m_block.size();
    }

    template <class Type, template <class> class Block>
    template <class... Args>
    void
    ArrayList<Type, Block>::for_each(const Action<void(Args...)>& func)
    {
        const auto& self =
            (const ArrayList<Type, Block>&) *this;

        for ( usize i = 0; i < m_count; i++ )
            func(m_block[i], i, self);
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::resize(usize size)
    {
        return m_block.resize(size);
    }

    template <class Type, template <class> class Block>
    template <class... Args>
    bool
    ArrayList<Type, Block>::clear(const Action<void(Args...)>& func)
    {
        const auto& self =
            (const ArrayList<Type, Block>&) *this;

        for ( usize i = 0; i < m_count; i++ )
            func(m_block[i], i, self);

        return m_block.resize(0);
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::clear()
    {
        return m_block.resize(0);
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::insert(const Type& value, isize index)
    {
        usize place = index;

        if ( is_full() == false ) {
            if ( index < 0 )
                place = m_count + index;

            for ( usize i = m_count; i > place; i-- )
                m_block[i] = move(m_block[i - 1]);

            m_count += 1;
            m_block[place] = value;

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::remove(isize index)
    {
        return false;
    }

    template <class Type, template <class> class Block>
    Type&
    ArrayList<Type, Block>::find(isize index)
    {
        usize place = index;

        if ( index < 0 )
            place = m_count + index;

        return m_block[place];
    }

    template <class Type, template <class> class Block>
    const Type&
    ArrayList<Type, Block>::find(isize index) const
    {
        usize place = index;

        if ( index < 0 )
            place = m_count + index;

        return m_block[place];
    }

    template <class Type, template <class> class Block>
    const Block<Type>&
    ArrayList<Type, Block>::block() const
    {
        return m_block;
    }

    template <class Type, template <class> class Block>
    Type&
    ArrayList<Type, Block>::operator[](isize index)
    {
        return find(index);
    }

    template <class Type, template <class> class Block>
    const Type&
    ArrayList<Type, Block>::operator[](isize index) const
    {
        return find(index);
    }
} // namespace ma
