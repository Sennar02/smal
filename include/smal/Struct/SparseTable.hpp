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
         * @param sparse
         * @param packed
         * @param values
         */
        SparseTable(
            const PagedArray<long>& sparse,
            const Array<long>&      packed,
            const Array<Type>&      values);

        /**
         * @brief
         *
         * @return long
         */
        long
        length() const;

        /**
         * @brief
         *
         * @return long
         */
        long
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
         * @return PagedArray<long>&
         */
        PagedArray<long>&
        sparse();

        /**
         * @brief
         *
         * @return const PagedArray<long>&
         */
        const PagedArray<long>&
        sparse() const;

        /**
         * @brief
         *
         * @return Array<long>&
         */
        Array<long>&
        packed();

        /**
         * @brief
         *
         * @return const Array<long>&
         */
        const Array<long>&
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
        contains(const long& key) const;

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
        insert(const long& key, const Type& value);

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
        insert(const long& key, Type&& value);

        /**
         * @brief
         *
         * @param key
         *
         * @return true
         * @return false
         */
        bool
        remove(const long& key);

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
        resize(long sparse, long packed);

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
        resize(float sparse, float packed);

        /**
         * @brief
         *
         * @param key
         *
         * @return Type&
         */
        Type&
        valueOf(const long& key);

        /**
         * @brief
         *
         * @param key
         *
         * @return const Type&
         */
        const Type&
        valueOf(const long& key) const;

        /**
         * @brief
         *
         * @param index
         *
         * @return Type&
         */
        Type&
        operator[](const long& index);

        /**
         * @brief
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        operator[](const long& index) const;

    private:
        /**
         * @brief
         */
        PagedArray<long> m_sparse;

        /**
         * @brief
         */
        Array<long> m_packed;

        /**
         * @brief
         */
        Array<Type> m_array;

        /**
         * @brief
         */
        long m_size;
    };
} // namespace smal

#include <smal/Struct/impl/SparseTable.tpp>

#endif // SMAL_STRUCT_SPARSE_SET_HPP
