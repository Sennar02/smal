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
    ArrayList<Type, Block>::ArrayList(const Alloc& alloc, u32 size, u32 count)
        : m_block {}
        , m_count {0}
    {
        m_block = Block<Type> {
            alloc,
            size,
        };

        if ( count > m_block.size() )
            count = m_block.size();

        m_count = count;
    }

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
    template <class Func>
    u32
    ArrayList<Type, Block>::index_of(const Type& value, Func&& func) const
    {
        for ( u32 i = 0; i < m_count; i++ ) {
            if ( func(m_block[i], value) == true )
                return i;
        }

        return g_max_u32;
    }

    template <class Type, template <class> class Block>
    u32
    ArrayList<Type, Block>::index_of(const Type& value) const
    {
        Action func = {[](const Type& block, const Type& value) {
            return block == value;
        }};

        return contains(value, func);
    }

    template <class Type, template <class> class Block>
    template <class Func>
    bool
    ArrayList<Type, Block>::contains(const Type& value, Func&& func) const
    {
        return index_of(value, func) != g_max_u32;
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::contains(const Type& value) const
    {
        Action func = {[](const Type& block, const Type& value) {
            return block == value;
        }};

        return contains(value, func);
    }

    template <class Type, template <class> class Block>
    template <class Func>
    void
    ArrayList<Type, Block>::for_each(Func&& func) const
    {
        for ( u32 i = 0; i < m_count; i++ )
            func((Type&) m_block[i], i, *this);
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::resize(u32 size)
    {
        return m_block.resize(size);
    }

    template <class Type, template <class> class Block>
    template <class Func>
    bool
    ArrayList<Type, Block>::clear(Func&& func)
    {
        using Self = ArrayList<Type, Block>;

        for ( u32 i = 0; i < m_count; i++ )
            func(m_block[i], i, (const Self&) *this);

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
    ArrayList<Type, Block>::insert(const Type& value, i32 index)
    {
        u32 place = index;

        if ( is_full() == false ) {
            if ( place > m_count ) place = m_count;
            if ( index < 0 ) place = m_count + index;
            if ( place > m_count ) place = 0;

            for ( u32 i = m_count; i > place; i-- )
                m_block[i] = move(m_block[i - 1]);

            m_count += 1;
            m_block[place] = value;

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::remove(i32 index)
    {
        u32 place = index;

        if ( is_empty() == false ) {
            if ( place > m_count ) place = m_count;
            if ( index < 0 ) place = m_count + index;
            if ( place > m_count ) place = 0;

            m_count -= 1;

            for ( u32 i = place; i < m_count; i++ )
                m_block[i] = move(m_block[i + 1]);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Block>
    Type&
    ArrayList<Type, Block>::find(i32 index)
    {
        u32 place = index;

        if ( index < 0 )
            place = m_count + index;

        return m_block[place];
    }

    template <class Type, template <class> class Block>
    const Type&
    ArrayList<Type, Block>::find(i32 index) const
    {
        u32 place = index;

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
    ArrayList<Type, Block>::operator[](i32 index)
    {
        return find(index);
    }

    template <class Type, template <class> class Block>
    const Type&
    ArrayList<Type, Block>::operator[](i32 index) const
    {
        return find(index);
    }
} // namespace ma
