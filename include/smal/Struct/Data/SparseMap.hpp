#ifndef SMAL_STRUCT_DATA_SPARSE_MAP_HPP
#define SMAL_STRUCT_DATA_SPARSE_MAP_HPP

#include <smal/Struct/define.hpp>

namespace smal
{
    template <class Type, template <class> class Array = PagedArray>
    class SparseMap
    {
    public:
        /**
         * @brief
         */
        SparseMap();

        /**
         * @brief
         *
         * @param origin
         * @param length
         */
        SparseMap(BaseOrigin* origin, usize length = 0);

        /**
         * @brief
         *
         * @param values
         */
        SparseMap(const Array<Type>& values);

        /**
         * @brief
         */
        virtual ~SparseMap() = default;

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
         * @param key
         * @param comp
         *
         * @return true
         * @return false
         */
        template <class Func>
        bool
        contains(usize key, Func comp) const;

        /**
         * @brief
         *
         * @param key
         *
         * @return true
         * @return false
         */
        bool
        contains(usize key) const;

        /**
         * @brief
         *
         * @tparam Func
         *
         * @param key
         * @param comp
         *
         * @return isize
         */
        template <class Func>
        isize
        indexOf(usize key, Func comp) const;

        /**
         * @brief
         *
         * @param key
         *
         * @return isize
         */
        isize
        indexOf(usize key) const;

        /**
         * @brief
         *
         * @tparam Func
         *
         * @param index
         * @param comp
         *
         * @return isize
         */
        template <class Func>
        isize
        keyOf(usize index, Func comp) const;

        /**
         * @brief
         *
         * @param index
         *
         * @return isize
         */
        isize
        keyOf(usize index) const;

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
         * @param origin
         *
         * @return SparseMap<Type, Array>
         */
        SparseMap<Type, Array>
        clone(BaseOrigin* origin) const;

        /**
         * @brief
         *
         * @param key
         * @param value
         *
         * @return true
         * @return false
         */
        bool
        insert(usize key, const Type& value);

        /**
         * @brief
         *
         * @param key
         * @param value
         *
         * @return true
         * @return false
         */
        bool
        insert(usize key, Type&& value);

        /**
         * @brief
         *
         * @param key
         *
         * @return true
         * @return false
         */
        bool
        remove(usize key);

        /**
         * @brief
         *
         * @param sparse
         * @param packed
         *
         * @return true
         * @return false
         */
        bool
        resize(usize sparse, usize packed);

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
         * @return PagedArray<Type>&
         */
        PagedArray<usize>&
        sparse();

        /**
         * @brief
         *
         * @return const PagedArray<Type>&
         */
        const PagedArray<usize>&
        sparse() const;

        /**
         * @brief
         *
         * @return PagedArray<Type>&
         */
        PagedArray<usize>&
        packed();

        /**
         * @brief
         *
         * @return const PagedArray<Type>&
         */
        const PagedArray<usize>&
        packed() const;

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
        find(usize index);

        /**
         * @brief
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        find(usize index) const;

        /**
         * @brief
         *
         * @param index
         *
         * @return Type&
         */
        Type&
        operator[](usize index);

        /**
         * @brief
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        operator[](usize index) const;

    private:
        /**
         * @brief
         *
         * @param key
         * @return true
         * @return false
         */
        bool
        growTo(usize key);

    private:
        /**
         * @brief
         */
        PagedArray<usize> m_sparse;

        /**
         * @brief
         */
        PagedArray<usize> m_packed;

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

#include <smal/Struct/impl/SparseMap.tpp>

#endif // SMAL_STRUCT_DATA_SPARSE_MAP_HPP
