#ifndef SMAL_MEMORY_PAGED_ARRAY_HPP
#define SMAL_MEMORY_PAGED_ARRAY_HPP

#include <smal/Memory/Origin/PoolOrigin.hpp>
#include <smal/Memory/PartTable.hpp>

namespace smal
{
    template <class Type>
    class PagedArray
    {
    public:
        static const usize SIZE = sizeof(Type);

    public:
        /**
         * @brief
         */
        PagedArray();

        /**
         * @brief
         *
         * @param origin
         * @param length
         */
        PagedArray(PoolOrigin* origin, usize length = 0);

        /**
         * @brief
         *
         * @param origin
         * @param table
         * @param length
         */
        PagedArray(PoolOrigin* origin, PartTable& table, usize length = 0);

        /**
         * @brief
         */
        virtual ~PagedArray();

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
         * @param pages
         *
         * @return true
         * @return false
         */
        bool
        attach(usize pages);

        /**
         * @brief
         *
         * @param pages
         *
         * @return true
         * @return false
         */
        bool
        detach(usize pages);

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

    public:
        /**
         * @brief
         */
        PoolOrigin* m_origin;

        /**
         * @brief
         */
        PartTable m_table;
    };
} // namespace smal

#include <smal/Memory/impl/PagedArray.tpp>

#endif // SMAL_MEMORY_PAGED_ARRAY_HPP
