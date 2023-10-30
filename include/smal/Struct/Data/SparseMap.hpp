#ifndef SMAL_STRUCT_DATA_SPARSE_MAP_HPP
#define SMAL_STRUCT_DATA_SPARSE_MAP_HPP

#include <smal/Struct/define.hpp>

namespace ma
{
    template <class Type, template <class> class Array = PagedArray>
    class SparseMap
    {
    public:
        /**
         *
         */
        SparseMap();

        /**
         *
         *
         * @param origin
         * @param size
         */
        SparseMap(BaseOrigin* origin, usize size = 0);

        /**
         *
         *
         * @param values
         */
        SparseMap(const Array<Type>& values);

        /**
         *
         */
        virtual ~SparseMap() = default;

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
         * @return usize
         */
        usize
        count() const;

        /**
         *
         *
         * @return True.
         * @return False.
         */
        bool
        is_empty() const;

        /**
         *
         *
         * @return True.
         * @return False.
         */
        bool
        is_full() const;

        /**
         *
         *
         * @tparam Func
         *
         * @param key
         * @param comp
         *
         * @return True.
         * @return False.
         */
        template <class Func>
        bool
        contains(usize key, Func comp) const;

        /**
         *
         *
         * @param key
         *
         * @return True.
         * @return False.
         */
        bool
        contains(usize key) const;

        /**
         *
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
        index_of(usize key, Func comp) const;

        /**
         *
         *
         * @param key
         *
         * @return isize
         */
        isize
        index_of(usize key) const;

        /**
         *
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
        key_of(usize index, Func comp) const;

        /**
         *
         *
         * @param index
         *
         * @return isize
         */
        isize
        key_of(usize index) const;

        /**
         *
         *
         * @tparam Func
         *
         * @param oper
         */
        template <class Func>
        void
        for_each(Func oper) const;

        /**
         *
         *
         * @param origin
         *
         * @return SparseMap<Type, Array>
         */
        SparseMap<Type, Array>
        clone(BaseOrigin* origin) const;

        /**
         *
         *
         * @param key
         * @param value
         *
         * @return True.
         * @return False.
         */
        bool
        insert(usize key, const Type& value);

        /**
         *
         *
         * @param key
         * @param value
         *
         * @return True.
         * @return False.
         */
        bool
        insert(usize key, Type&& value);

        /**
         *
         *
         * @param key
         *
         * @return True.
         * @return False.
         */
        bool
        remove(usize key);

        /**
         *
         *
         * @param sparse
         * @param packed
         *
         * @return True.
         * @return False.
         */
        bool
        resize(usize sparse, usize packed);

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
         * @return PagedArray<Type>&
         */
        PagedArray<usize>&
        sparse();

        /**
         *
         *
         * @return const PagedArray<Type>&
         */
        const PagedArray<usize>&
        sparse() const;

        /**
         *
         *
         * @return PagedArray<Type>&
         */
        PagedArray<usize>&
        packed();

        /**
         *
         *
         * @return const PagedArray<Type>&
         */
        const PagedArray<usize>&
        packed() const;

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
        find(usize index);

        /**
         *
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        find(usize index) const;

        /**
         *
         *
         * @param index
         *
         * @return Type&
         */
        Type&
        operator[](usize index);

        /**
         *
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        operator[](usize index) const;

    private:
        /**
         *
         *
         * @param key
         * @return True.
         * @return False.
         */
        bool
        grow_to(usize key);

    private:
        /**
         *
         */
        PagedArray<usize> m_sparse;

        /**
         *
         */
        PagedArray<usize> m_packed;

        /**
         *
         */
        Array<Type> m_array;

        /**
         *
         */
        usize m_count;
    };
} // namespace ma

#include <smal/Struct/impl/SparseMap.tpp>

#endif // SMAL_STRUCT_DATA_SPARSE_MAP_HPP
