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
        ArrayList(const Block<Type>& block, u32 count = 0);

        /**
         *
         */
        template <class Alloc>
        ArrayList(const Alloc& alloc, u32 size, u32 count = 0);

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
        is_empty() const;

        /**
         *
         */
        bool
        is_full() const;

        /**
         *
         */
        template <class Func>
        u32
        index_of(const Type& value, Func&& func) const;

        /**
         *
         */
        u32
        index_of(const Type& value) const;

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
        template <class Func>
        void
        for_each(Func&& func) const;

        /**
         *
         */
        bool
        resize(u32 size);

        /**
         *
         */
        template <class Func>
        bool
        clear(Func&& func);

        /**
         *
         */
        bool
        clear();

        /**
         *
         */
        bool
        insert(const Type& value, i32 index = g_max_u32);

        /**
         *
         */
        bool
        remove(i32 index = g_max_u32);

        /**
         *
         */
        Type&
        find(i32 index);

        /**
         *
         */
        const Type&
        find(i32 index) const;

        /**
         *
         */
        const Block<Type>&
        block() const;

        /**
         *
         */
        Type&
        operator[](i32 index);

        /**
         *
         */
        const Type&
        operator[](i32 index) const;

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
} // namespace ma

#include <smal/Struct/impl/ArrayList.tpp>

#endif // SMAL_STRUCT_ARRAY_LIST_HPP
