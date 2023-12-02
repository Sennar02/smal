#include <smal/Struct/ArrayList.hpp>

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
    ArrayList<Type, Block>::ArrayList(const Alloc& alloc, u32 size, u32 count)
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
    template <class Func>
    u32
    ArrayList<Type, Block>::indexOf(const Type& value, u32 start, Func&& func) const
    {
        u32 pos = 0;

        for ( u32 i = 0; i < m_count; i++ ) {
            pos = (start + i) % m_count;

            if ( func(m_block[pos], value) == true )
                return i;
        }

        return g_max_u32;
    }

    template <class Type, template <class> class Block>
    u32
    ArrayList<Type, Block>::indexOf(const Type& value, u32 start) const
    {
        Action func = {
            [](const Type& inner, const Type& value) {
                return inner == value;
            },
        };

        return contains(value, start, func);
    }

    template <class Type, template <class> class Block>
    template <class Func>
    bool
    ArrayList<Type, Block>::contains(const Type& value, u32 start, Func&& func) const
    {
        return indexOf(value, start, func) != g_max_u32;
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::contains(const Type& value, u32 start) const
    {
        return indexOf(value, start) != g_max_u32;
    }

    template <class Type, template <class> class Block>
    template <class Func>
    void
    ArrayList<Type, Block>::forEach(Func&& func) const
    {
        const auto& self = *this;

        for ( u32 i = 0; i < m_count; i++ )
            func((Type&) m_block[i], i, self);
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
        const auto& self = *this;

        for ( u32 i = 0; i < m_count; i++ )
            func(m_block[i], i, self);

        return resize(0);
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::clear()
    {
        return resize(0);
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::insert(const Type& value, i32 index)
    {
        u32 pos = index;

        if ( isFull() == false ) {
            if ( pos > m_count ) pos = m_count;
            if ( index < 0 ) pos = m_count + index;
            if ( pos > m_count ) pos = 0;

            for ( u32 i = m_count; i > pos; i-- )
                m_block[i] = move(m_block[i - 1]);

            m_count += 1;
            m_block[pos] = value;

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Block>
    bool
    ArrayList<Type, Block>::remove(i32 index)
    {
        u32 pos = index;

        if ( isEmpty() == false ) {
            if ( pos > m_count ) pos = m_count;
            if ( index < 0 ) pos = m_count + index;
            if ( pos > m_count ) pos = 0;

            m_count -= 1;

            for ( u32 i = pos; i < m_count; i++ )
                m_block[i] = move(m_block[i + 1]);

            return true;
        }

        return false;
    }

    template <class Type, template <class> class Block>
    Type&
    ArrayList<Type, Block>::find(i32 index)
    {
        u32 pos = index;

        if ( index < 0 )
            pos = m_count + index;

        return m_block[pos];
    }

    template <class Type, template <class> class Block>
    const Type&
    ArrayList<Type, Block>::find(i32 index) const
    {
        u32 pos = index;

        if ( index < 0 )
            pos = m_count + index;

        return m_block[pos];
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
