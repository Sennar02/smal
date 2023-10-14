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
         * @param values
         */
        Vector(const Array<Type>& values);

        /**
         * @brief
         */
        virtual ~Vector();

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
         * @param value
         * @param index
         *
         * @return true
         * @return false
         */
        bool
        insert(const Type& value, usize index = -1);

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
        insert(Type&& value, usize index = -1);

        /**
         * @brief
         *
         * @param index
         *
         * @return true
         * @return false
         */
        bool
        remove(usize index = -1);

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
         */
        Array<Type> m_array;

        /**
         * @brief
         */
        usize m_size;
    };
} // namespace smal

#include <smal/Struct/impl/Vector.tpp>

#endif // SMAL_STRUCT_VECTOR_HPP
