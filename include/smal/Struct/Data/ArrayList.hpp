#ifndef SMAL_STRUCT_DATA_ARRAY_LIST_HPP
#define SMAL_STRUCT_DATA_ARRAY_LIST_HPP

#include <smal/Struct/define.hpp>

namespace ma
{
    template <class Type, template <class> class Array = PagedArray>
    class ArrayList
    {
    public:
        /**
         *
         */
        ArrayList();

        /**
         *
         *
         * @param origin
         * @param length
         */
        ArrayList(BaseOrigin* origin, usize length = 0);

        /**
         *
         *
         * @param values
         */
        ArrayList(const Array<Type>& values);

        /**
         *
         */
        virtual ~ArrayList() = default;

        /**
         *
         *
         * @return usize
         */
        usize
        capacity() const;

        /**
         *
         *
         * @return usize
         */
        usize
        size() const;

        /**
         *
         *
         * @return True.
         * @return False.
         */
        bool
        isEmpty() const;

        /**
         *
         *
         * @return True.
         * @return False.
         */
        bool
        isFull() const;

        /**
         *
         *
         * @tparam Func
         *
         * @param value
         * @param comp
         *
         * @return True.
         * @return False.
         */
        template <class Func>
        bool
        contains(const Type& value, Func comp) const;

        /**
         *
         *
         * @param value
         *
         * @return True.
         * @return False.
         */
        bool
        contains(const Type& value) const;

        /**
         *
         *
         * @tparam Func
         *
         * @param value
         * @param comp
         *
         * @return isize
         */
        template <class Func>
        isize
        indexOf(const Type& value, Func comp) const;

        /**
         *
         *
         * @param value
         *
         * @return isize
         */
        isize
        indexOf(const Type& value) const;

        /**
         *
         *
         * @tparam Func
         *
         * @param oper
         */
        template <class Func>
        void
        forEach(Func oper) const;

        /**
         *
         *
         * @param origin
         *
         * @return ArrayList<Type, Array>
         */
        ArrayList<Type, Array>
        clone(BaseOrigin* origin) const;

        /**
         *
         *
         * @param value
         * @param index
         *
         * @return True.
         * @return False.
         */
        bool
        insert(const Type& value, isize index = -1);

        /**
         *
         *
         * @param value
         * @param index
         *
         * @return True.
         * @return False.
         */
        bool
        insert(Type&& value, isize index = -1);

        /**
         *
         *
         * @param index
         *
         * @return True.
         * @return False.
         */
        bool
        remove(isize index = -1);

        /**
         *
         *
         * @param length
         *
         * @return True.
         * @return False.
         */
        bool
        resize(usize length);

        /**
         *
         *
         * @tparam Algo
         * @tparam Comp
         *
         * @param comp
         */
        template <class Algo, class Comp>
        void
        sort(Comp comp);

        /**
         *
         *
         * @return Array<Type>&
         */
        Array<Type>&
        values();

        /**
         *
         *
         * @return const Array<Type>&
         */
        const Array<Type>&
        values() const;

        /**
         *
         *
         * @param index
         *
         * @return Type&
         */
        Type&
        find(isize index);

        /**
         *
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        find(isize index) const;

        /**
         *
         *
         * @param index
         *
         * @return Type&
         */
        Type&
        operator[](isize index);

        /**
         *
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        operator[](isize index) const;

    private:
        /**
         *
         *
         * @param index
         * @param limit
         *
         * @return usize
         */
        usize
        limit(isize index, usize limit) const;

    private:
        /**
         *
         */
        Array<Type> m_array;

        /**
         *
         */
        usize m_size;
    };
} // namespace ma

#include <smal/Struct/impl/ArrayList.tpp>

#endif // SMAL_STRUCT_DATA_ARRAY_LIST_HPP
