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
         * @param origin
         * @param ptable
         */
        Vector(PageAlloc& origin, PageTable& ptable);

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
         * @param pages
         *
         * @return true
         * @return false
         */
        bool
        expand(long pages);

        /**
         * @brief
         *
         * @param pages
         *
         * @return true
         * @return false
         */
        bool
        shrink(long pages);

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
        PageAlloc* m_origin;

        /**
         * @brief
         */
        PageTable* m_ptable;

        /**
         * @brief
         */
        long m_size;
    };
} // namespace smal

#include <smal/Struct/impl/Vector.tpp>

#endif // SMAL_STRUCT_VECTOR_HPP
