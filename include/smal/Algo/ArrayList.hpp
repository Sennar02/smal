#ifndef SMAL_ALGO_ARRAY_LIST_HPP
#define SMAL_ALGO_ARRAY_LIST_HPP

#include <smal/Algo/define.hpp>

namespace ma
{
    template <class Item, template <class> class Block = PagedBlock>
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
        ArrayList(const Block<Item>& block, u32 count = 0);

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
        indexOf(const Item& item, Iter& iter, Func&& func) const;

        /**
         *
         */
        template <class Func>
        u32
        indexOf(const Item& item, Func&& func) const;

        /**
         *
         */
        u32
        indexOf(const Item& item) const;

        /**
         *
         */
        template <class Iter, class Func>
        bool
        contains(const Item& item, Iter& iter, Func&& func) const;

        /**
         *
         */
        template <class Func>
        bool
        contains(const Item& item, Func&& func) const;

        /**
         *
         */
        bool
        contains(const Item& item) const;

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
        insert(const Item& item, u32 index = g_max_u32);

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
        Item*
        search(u32 index) const;

        /**
         *
         */
        Item&
        find(u32 index) const;

        /**
         *
         */
        const Block<Item>&
        block() const;

        /**
         *
         */
        Item&
        operator[](u32 index) const;

    private:
        /**
         *
         */
        Block<Item> m_block;

        /**
         *
         */
        u32 m_count;
    };

    template <class Item, template <class> class Block>
    ArrayList(const Block<Item>&)
        -> ArrayList<Item, Block>;

    template <class Item, template <class> class Block>
    ArrayList(const Block<Item>&, u32)
        -> ArrayList<Item, Block>;

    template <class Item, template <class> class Block>
    class ArrayListForwIter
    {
    private:
        using List = ArrayList<Item, Block>;

    public:
        /**
         *
         */
        ArrayListForwIter(const List& list);

        /**
         *
         */
        u32
        index() const;

        /**
         *
         */
        Item&
        item();

        /**
         *
         */
        const Item&
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
        reset();

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

    template <class Item, template <class> class Block>
    ArrayListForwIter(const ArrayList<Item, Block>&)
        -> ArrayListForwIter<Item, Block>;

    template <class Item, template <class> class Block>
    class ArrayListBackIter
    {
    private:
        using List = ArrayList<Item, Block>;

    public:
        /**
         *
         */
        ArrayListBackIter(const List& list);

        /**
         *
         */
        u32
        index() const;

        /**
         *
         */
        Item&
        item();

        /**
         *
         */
        const Item&
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
        reset();

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

    template <class Item, template <class> class Block>
    ArrayListBackIter(const ArrayList<Item, Block>&)
        -> ArrayListBackIter<Item, Block>;
} // namespace ma

#include <smal/Algo/impl/ArrayList.tpp>

#endif // SMAL_ALGO_ARRAY_LIST_HPP
