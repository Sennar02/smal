#ifndef SMAL_STRUCT_VECTOR_HPP
#define SMAL_STRUCT_VECTOR_HPP

#include <smal/Struct/depend.hpp>

namespace smal
{
    template <class Type>
    class Vector
    {
    public:
        /**
         * @brief
         */
        static const long TYPE_SIZE = sizeof(Type);

    public:
        /**
         * @brief
         *
         * @param table
         */
        Vector(PageTable& table);

        /**
         * @brief
         *
         * @return long
         */
        long
        get_length() const;

        /**
         * @brief
         *
         * @return long
         */
        long
        get_size() const;

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
        PageTable* m_table;

        /**
         * @brief
         */
        long m_size;
    };
} // namespace smal

#include <smal/Struct/impl/Vector.tpp>

#endif // SMAL_STRUCT_VECTOR_HPP
