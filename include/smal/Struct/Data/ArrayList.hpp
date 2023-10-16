#ifndef SMAL_STRUCT_ARRAY_LIST_HPP
#define SMAL_STRUCT_ARRAY_LIST_HPP

#include <smal/Struct/define.hpp>

namespace smal
{
    template <class Type, template <class> class Array = PagedArray>
    class ArrayList
    {
    public:
        /**
         * @brief
         */
        ArrayList();

        /**
         * @brief
         *
         * @param origin
         * @param length
         */
        ArrayList(BaseOrigin* origin, usize length = 0);

        /**
         * @brief
         *
         * @param values
         */
        ArrayList(const Array<Type>& values);

        /**
         * @brief
         */
        virtual ~ArrayList() = default;

        /**
         * @brief
         *
         * @return usize
         */
        usize
        capacity() const;

        /**
         * @brief
         *
         * @return usize
         */
        usize
        size() const;

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool
        isEmpty() const;

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool
        isFull() const;

        /**
         * @brief
         *
         * @tparam Func
         *
         * @param value
         * @param comp
         *
         * @return true
         * @return false
         */
        template <class Func>
        bool
        contains(const Type& value, Func comp) const;

        /**
         * @brief
         *         *
         * @param value
         * @param comp
         *
         * @return true
         * @return false
         */
        bool
        contains(const Type& value) const;

        /**
         * @brief
         *
         * @tparam Func
         *
         * @param oper
         */
        template <class Func>
        void
        forEach(Func oper) const;

        /**
         * @brief
         *
         * @param value
         * @param index
         *
         * @return true
         * @return false
         */
        bool
        insert(const Type& value, isize index = -1);

        /**
         * @brief
         *
         * @param value
         * @param index
         *
         * @return true
         * @return false
         */
        bool
        insert(Type&& value, isize index = -1);

        /**
         * @brief
         *
         * @param index
         *
         * @return true
         * @return false
         */
        bool
        remove(isize index = -1);

        /**
         * @brief
         *
         * @param length
         *
         * @return true
         * @return false
         */
        bool
        resize(usize length);

        /**
         * @brief
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
         * @brief
         *
         * @return Array<Type>&
         */
        Array<Type>&
        values();

        /**
         * @brief
         *
         * @return const Array<Type>&
         */
        const Array<Type>&
        values() const;

        /**
         * @brief
         *
         * @param index
         *
         * @return Type&
         */
        Type&
        find(isize index);

        /**
         * @brief
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        find(isize index) const;

        /**
         * @brief
         *
         * @param index
         *
         * @return Type&
         */
        Type&
        operator[](isize index);

        /**
         * @brief
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        operator[](isize index) const;

    private:
        /**
         * @brief
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
         * @brief
         */
        Array<Type> m_array;

        /**
         * @brief
         */
        usize m_size;
    };
} // namespace smal

#include <smal/Struct/impl/ArrayList.tpp>

#endif // SMAL_STRUCT_ARRAY_LIST_HPP
