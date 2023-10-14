#ifndef SMAL_MEMORY_PAGE_ARRAY_HPP
#define SMAL_MEMORY_PAGE_ARRAY_HPP

#include <smal/Memory/PageAlloc.hpp>
#include <smal/Memory/PageTable.hpp>

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
        PagedArray(PageAlloc& origin, usize length = 0);

        /**
         * @brief
         *
         * @param origin
         * @param table
         * @param length
         */
        PagedArray(PageAlloc& origin, PageTable& table, usize length = 0);

        /**
         * @brief
         *
         * @param origin
         * @param memory
         * @param length
         */
        PagedArray(PageAlloc& origin, void* memory, usize length);

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
        PageTable m_table;

        /**
         * @brief
         */
        PageAlloc* m_origin;
    };
} // namespace smal

#include <smal/Memory/impl/PagedArray.tpp>

#endif // SMAL_MEMORY_PAGE_ARRAY_HPP
