#ifndef SMAL_STRUCT_SPARSE_SET_HPP
#define SMAL_STRUCT_SPARSE_SET_HPP

#include <smal/Struct/define.hpp>

namespace smal
{
    template <class Type, template <class> class Array = FixedArray>
    class SparseMap
    {
    public:
        SparseMap();

        SparseMap(const PagedArray<long>& table, const PagedArray<long>& dense, const Array<Type>& array);

        SparseMap(PageAlloc& origin, const Array<Type>& array);

        long
        length() const;

        long
        size() const;

        bool
        isFull() const;

        bool
        isEmpty() const;

        bool
        insert(long key, const Type& item);

        bool
        insert(long key, Type&& item);

        bool
        remove(long key);

        bool
        contains(long key) const;

        bool
        resize(long keys, long vals);

        Type&
        access(long index = -1);

        const Type&
        access(long index = -1) const;

        Type&
        operator[](long index);

        const Type&
        operator[](long index) const;

    private:
        Array<long> m_table;
        Array<long> m_dense;
        Array<Type> m_array;
        long        m_size;
    };
} // namespace smal

#include <smal/Struct/impl/SparseMap.tpp>

#endif // SMAL_STRUCT_SPARSE_SET_HPP
