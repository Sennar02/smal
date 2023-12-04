#ifndef SMAL_ALGO_ARRAY_LIST_HPP
#define SMAL_ALGO_ARRAY_LIST_HPP

#include <smal/Algo/define.hpp>

namespace ma
{
    template <class Type, template <class> class Block = PagedBlock>
    class ArrayList
    {
    public:
        /**
         *
         */
        ArrayList();

        /**
         *
         */
        ArrayList(const Block<Type>& block, u32 count = 0);

        /**
         *
         */
        template <class Alloc>
        ArrayList(Alloc& alloc, u32 size, u32 count = 0);

        /**
         *
         */
        virtual ~ArrayList() = default;

        /**
         *
         */
        u32
        size() const;

        /**
         *
         */
        u32
        count() const;

        /**
         *
         */
        bool
        isEmpty() const;

        /**
         *
         */
        bool
        isFull() const;

        /**
         *
         */
        template <class Iter, class Func>
        u32
        indexOf(const Type& value, Iter& iter, Func&& func) const;

        /**
         *
         */
        template <class Func>
        u32
        indexOf(const Type& value, Func&& func) const;

        /**
         *
         */
        u32
        indexOf(const Type& value) const;

        /**
         *
         */
        template <class Iter, class Func>
        bool
        contains(const Type& value, Iter& iter, Func&& func) const;

        /**
         *
         */
        template <class Func>
        bool
        contains(const Type& value, Func&& func) const;

        /**
         *
         */
        bool
        contains(const Type& value) const;

        /**
         *
         */
        template <class Iter, class Func>
        void
        forEach(Iter& iter, Func&& func) const;

        /**
         *
         */
        template <class Func>
        void
        forEach(Func&& func) const;

        /**
         *
         */
        bool
        resize(u32 size);

        /**
         *
         */
        bool
        insert(const Type& value, u32 index = g_max_u32);

        /**
         *
         */
        bool
        remove(u32 index = g_max_u32);

        /**
         *
         */
        template <class Iter, class Func>
        void
        clear(Iter& iter, Func&& func);

        /**
         *
         */
        template <class Func>
        void
        clear(Func&& func);

        /**
         *
         */
        Type&
        find(u32 index) const;

        /**
         *
         */
        const Block<Type>&
        block() const;

        /**
         *
         */
        Type&
        operator[](u32 index) const;

    private:
        /**
         *
         */
        Block<Type> m_block;

        /**
         *
         */
        u32 m_count;
    };

    template <class Type, template <class> class Block>
    ArrayList(const Block<Type>&)
        -> ArrayList<Type, Block>;

    template <class Type, template <class> class Block>
    ArrayList(const Block<Type>&, u32)
        -> ArrayList<Type, Block>;

    template <class Type, template <class> class Block>
    class ArrayListForwIter
    {
    private:
        using List = ArrayList<Type, Block>;

    public:
        /**
         *
         */
        ArrayListForwIter(const List& list, u32 start = 0);

        /**
         *
         */
        u32
        index() const;

        /**
         *
         */
        Type&
        item();

        /**
         *
         */
        const Type&
        item() const;

        /**
         *
         */
        bool
        hasNext() const;

        /**
         *
         */
        bool
        next();

        /**
         *
         */
        void
        clear(u32 start = 0);

    private:
        /**
         *
         */
        const List& m_list;

        /**
         *
         */
        u32 m_index;
    };

    template <class Type, template <class> class Block>
    ArrayListForwIter(ArrayList<Type, Block>&)
        -> ArrayListForwIter<Type, Block>;

    template <class Type, template <class> class Block>
    class ArrayListBackIter
    {
    private:
        using List = ArrayList<Type, Block>;

    public:
        /**
         *
         */
        ArrayListBackIter(const List& list, u32 start = 0);

        /**
         *
         */
        u32
        index() const;

        /**
         *
         */
        Type&
        item();

        /**
         *
         */
        const Type&
        item() const;

        /**
         *
         */
        bool
        hasNext() const;

        /**
         *
         */
        bool
        next();

        /**
         *
         */
        void
        clear(u32 start = 0);

    private:
        /**
         *
         */
        const List& m_list;

        /**
         *
         */
        u32 m_index;
    };

    template <class Type, template <class> class Block>
    ArrayListBackIter(ArrayList<Type, Block>&)
        -> ArrayListBackIter<Type, Block>;
} // namespace ma

#include <smal/Algo/impl/ArrayList.tpp>

#endif // SMAL_ALGO_ARRAY_LIST_HPP
