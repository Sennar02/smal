#ifndef SMAL_ALGO_ARRAY_LIST_HPP
#define SMAL_ALGO_ARRAY_LIST_HPP

#include <smal/Algo/define.hpp>

namespace ma
{
    template <class Item, class Layout = FixedLayout>
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
        ArrayList(const Layout& array);

        /**
         *
         */
        template <class... Args>
        ArrayList(Args&&... args);

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
        void
        clear();

        /**
         *
         */
        Item&
        find(u32 index, Item& deflt) const;

        /**
         *
         */
        Item&
        find(u32 index) const;

        /**
         *
         */
        const Array<Item, Layout>&
        array() const;

        /**
         *
         */
        Item&
        operator[](u32 index) const;

    private:
        /**
         *
         */
        Array<Item, Layout> m_array;

        /**
         *
         */
        u32 m_count;
    };

    template <class Item, class Layout>
    class ArrayListForwIter
    {
    private:
        using List = ArrayList<Item, Layout>;

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

    template <class Item, class Layout>
    class ArrayListBackIter
    {
    private:
        using List = ArrayList<Item, Layout>;

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

    template <class Item, class Layout>
    ArrayList(const Layout&)
        -> ArrayList<Item, Layout>;

    template <class Item, class Layout>
    ArrayListForwIter(const ArrayList<Item, Layout>&)
        -> ArrayListForwIter<Item, Layout>;

    template <class Item, class Layout>
    ArrayListBackIter(const ArrayList<Item, Layout>&)
        -> ArrayListBackIter<Item, Layout>;
} // namespace ma

#include <smal/Algo/inline/ArrayList.inl>

#endif // SMAL_ALGO_ARRAY_LIST_HPP
