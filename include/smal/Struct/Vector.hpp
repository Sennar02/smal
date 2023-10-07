#ifndef SMAL_STRUCT_VECTOR_HPP
#define SMAL_STRUCT_VECTOR_HPP

#include <smal/Struct/define.hpp>

namespace smal
{
    template <class Type, template <class> class Array = PagedArray>
    class Vector
    {
    public:
        /**
         * @brief
         */
        Vector();

        /**
         * @brief
         *
         * @param array
         */
        Vector(const Array<Type>& array);

        /**
         * @brief
         */
        virtual ~Vector();

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
         * @param value
         * @param index
         *
         * @return true
         * @return false
         */
        bool
        insert(const Type& value, long index = -1);

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
        insert(Type&& value, long index = -1);

        /**
         * @brief
         *
         * @param index
         *
         * @return true
         * @return false
         */
        bool
        remove(long index = -1);

        /**
         * @brief
         *
         * @param length
         *
         * @return true
         * @return false
         */
        bool
        resize(long length);

        /**
         * @brief
         *
         * @param index
         *
         * @return Type&
         */
        Type&
        access(long index = -1);

        /**
         * @brief
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        access(long index = -1) const;

        /**
         * @brief
         *
         * @param index
         *
         * @return Type&
         */
        Type&
        operator[](long index);

        /**
         * @brief
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        operator[](long index) const;

    private:
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

#include <smal/Struct/impl/Vector.tpp>

#endif // SMAL_STRUCT_VECTOR_HPP
