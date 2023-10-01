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
         * @param item
         * @param index
         *
         * @return true
         * @return false
         */
        bool
        insert(const Type& item, long index = -1);

        /**
         * @brief
         *
         * @param item
         * @param index
         *
         * @return true
         * @return false
         */
        bool
        insert(Type&& item, long index = -1);

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
