#ifndef SMAL_ALGO_ARRAY_STACK_HPP
#define SMAL_ALGO_ARRAY_STACK_HPP

#include <smal/Algo/define.hpp>

namespace ma
{
    template <class Item, template <class> class Array = FixedBuffer>
    class ArrayStack
    {
    public:
        /**
         *
         */
        ArrayStack();

        /**
         *
         */
        ArrayStack(Array<Item>&& array);

        /**
         *
         */
        template <class... Args>
        ArrayStack(Args&&... args);

        /**
         *
         */
        virtual ~ArrayStack() = default;

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
        insert(const Item& item);

        /**
         *
         */
        bool
        remove();

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
        const Array<Item>&
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
        Array<Item> m_array;

        /**
         *
         */
        u32 m_count;
    };

    template <class Item, template <class> class Array>
    class ArrayStackForwIter
    {
    private:
        using Stack = ArrayStack<Item, Array>;

    public:
        /**
         *
         */
        ArrayStackForwIter(const Stack& stack);

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
        const Stack& m_stack;

        /**
         *
         */
        u32 m_index;
    };

    template <class Item, template <class> class Array>
    ArrayStackForwIter(const ArrayStack<Item, Array>&)
        -> ArrayStackForwIter<Item, Array>;

    template <class Item, template <class> class Array>
    class ArrayStackBackIter
    {
    private:
        using Stack = ArrayStack<Item, Array>;

    public:
        /**
         *
         */
        ArrayStackBackIter(const Stack& stack);

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
        const Stack& m_stack;

        /**
         *
         */
        u32 m_index;
    };

    template <class Item, template <class> class Array>
    ArrayStackBackIter(const ArrayStack<Item, Array>&)
        -> ArrayStackBackIter<Item, Array>;
} // namespace ma

#include <smal/Algo/inline/ArrayStack.inl>

#endif // SMAL_ALGO_ARRAY_STACK_HPP
