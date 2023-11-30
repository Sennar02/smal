#ifndef SMAL_STRUCT_ARRAY_LIST_HPP
#define SMAL_STRUCT_ARRAY_LIST_HPP

#include <smal/Struct/define.hpp>

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
        ArrayList(const Block<Type>& block, usize count = 0);

        /**
         *
         */
        template <class Alloc>
        ArrayList(const Alloc& alloc, usize size, usize count = 0);

        /**
         *
         */
        virtual ~ArrayList() = default;

        /**
         *
         */
        usize
        size() const;

        /**
         *
         */
        usize
        count() const;

        /**
         *
         */
        bool
        is_empty() const;

        /**
         *
         */
        bool
        is_full() const;

        /**
         *
         */
        template <class... Args>
        usize
        index_of(const Type& value, const Action<bool(Args...)>& func) const;

        /**
         *
         */
        usize
        index_of(const Type& value) const;

        /**
         *
         */
        template <class... Args>
        bool
        contains(const Type& value, const Action<bool(Args...)>& func) const;

        /**
         *
         */
        bool
        contains(const Type& value) const;

        /**
         *
         */
        template <class... Args>
        void
        for_each(const Action<void(Args...)>& func) const;

        /**
         *
         */
        bool
        resize(usize size);

        /**
         *
         */
        template <class... Args>
        bool
        clear(const Action<void(Args...)>& func);

        /**
         *
         */
        bool
        clear();

        /**
         *
         */
        bool
        insert(const Type& value, isize index = g_max_usize);

        /**
         *
         */
        bool
        remove(isize index = g_max_usize);

        /**
         *
         */
        Type&
        find(isize index);

        /**
         *
         */
        const Type&
        find(isize index) const;

        /**
         *
         */
        const Block<Type>&
        block() const;

        /**
         *
         */
        Type&
        operator[](isize index);

        /**
         *
         */
        const Type&
        operator[](isize index) const;

    private:
        /**
         *
         */
        Block<Type> m_block;

        /**
         *
         */
        usize m_count;
    };

    template <class Type, template <class> class Block>
    ArrayList(const Block<Type>&)
        -> ArrayList<Type, Block>;

    template <class Type, template <class> class Block>
    ArrayList(const Block<Type>&, usize)
        -> ArrayList<Type, Block>;
} // namespace ma

#include <smal/Struct/impl/ArrayList.tpp>

#endif // SMAL_STRUCT_ARRAY_LIST_HPP
