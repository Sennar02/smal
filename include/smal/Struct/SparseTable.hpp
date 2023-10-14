#ifndef SMAL_STRUCT_SPARSE_SET_HPP
#define SMAL_STRUCT_SPARSE_SET_HPP

#include <smal/Struct/define.hpp>

namespace smal
{
    template <class Type, template <class> class Array = PagedArray>
    class SparseTable
    {
    public:
        /**
         * @brief
         */
        SparseTable();

        /**
         * @brief
         *
         * @param origin
         * @param length
         */
        SparseTable(PageAlloc& origin, usize length = 0);

        /**
         * @brief
         *
         * @param sparse
         * @param packed
         * @param values
         */
        SparseTable(
            const PagedArray<usize>& sparse,
            const PagedArray<usize>& packed,
            const Array<Type>&       values);

        /**
         * @brief
         *
         * @return usize
         */
        usize
        length() const;

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
        isFull() const;

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
         * @return PagedArray<usize>&
         */
        PagedArray<usize>&
        sparse();

        /**
         * @brief
         *
         * @return const PagedArray<usize>&
         */
        const PagedArray<usize>&
        sparse() const;

        /**
         * @brief
         *
         * @return PagedArray<usize>&
         */
        PagedArray<usize>&
        packed();

        /**
         * @brief
         *
         * @return const PagedArray<usize>&
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
         * @param key
         *
         * @return true
         * @return false
         */
        bool
        contains(const usize& key) const;

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
        insert(const usize& key, const Type& value);

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
        insert(const usize& key, Type&& value);

        /**
         * @brief
         *
         * @param key
         *
         * @return true
         * @return false
         */
        bool
        remove(const usize& key);

        /**
         * @brief
         *
         * @param sparse
         * @param packed
         * @param values
         *
         * @return true
         * @return false
         */
        bool
        resize(usize sparse, usize packed, usize values);

        /**
         * @brief
         *
         * @param key
         *
         * @return Type&
         */
        usize
        indexOf(const usize& key) const;

        /**
         * @brief
         *
         * @param index
         *
         * @return usize
         */
        usize
        keyOf(const usize& index) const;

        /**
         * @brief
         *
         * @param key
         *
         * @return Type&
         */
        Type&
        valueOf(const usize& key);

        /**
         * @brief
         *
         * @param key
         *
         * @return const Type&
         */
        const Type&
        valueOf(const usize& key) const;

        // /**
        //  * @brief
        //  *
        //  * @param func
        //  *
        //  * @return true
        //  * @return false
        //  */
        // void
        // sort(bool (*func)(const usize& value, const usize& other));

        /**
         * @brief
         *
         * @param index
         *
         * @return Type&
         */
        Type&
        operator[](const usize& index);

        /**
         * @brief
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        operator[](const usize& index) const;

    private:
        /**
         * @brief
         *
         * @param key
         *
         * @return true
         * @return false
         */
        bool
        resize(const usize& key);

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

#include <smal/Struct/impl/SparseTable.tpp>

#endif // SMAL_STRUCT_SPARSE_SET_HPP
