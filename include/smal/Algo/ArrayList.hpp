#ifndef SMAL_ALGO_ARRAY_LIST_HPP
#define SMAL_ALGO_ARRAY_LIST_HPP

#include <smal/Algo/define.hpp>

namespace ma
{
    template <class Item, template <class> class Buffer = FixedBuffer>
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
        const Buffer<Item>&
        buffer() const;

        /**
         *
         */
        Item&
        operator[](u32 index) const;

    private:
        /**
         *
         */
        Buffer<Item> m_array;

        /**
         *
         */
        u32 m_count;
    };

    template <class Item, template <class> class Buffer>
    ArrayList(Buffer<Item>&&)
        -> ArrayList<Item, Buffer>;

    template <class Item, template <class> class Buffer>
    class ArrayListForwIter
    {
    private:
        using List = ArrayList<Item, Buffer>;

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

    template <class Item, template <class> class Buffer>
    ArrayListForwIter(const ArrayList<Item, Buffer>&)
        -> ArrayListForwIter<Item, Buffer>;

    template <class Item, template <class> class Buffer>
    class ArrayListBackIter
    {
    private:
        using List = ArrayList<Item, Buffer>;

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

    template <class Item, template <class> class Buffer>
    ArrayListBackIter(const ArrayList<Item, Buffer>&)
        -> ArrayListBackIter<Item, Buffer>;
} // namespace ma

#include <smal/Algo/inline/ArrayList.inl>

#endif // SMAL_ALGO_ARRAY_LIST_HPP
