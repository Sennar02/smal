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
        static const long SIZE = sizeof(Type);

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
        PagedArray(PageAlloc& origin, long length = 0);

        /**
         * @brief
         *
         * @param origin
         * @param table
         * @param length
         */
        PagedArray(PageAlloc& origin, PageTable& table, long length = 0);

        /**
         * @brief
         *
         * @param origin
         * @param memory
         * @param length
         */
        PagedArray(PageAlloc& origin, void* memory, long length);

        /**
         * @brief
         */
        virtual ~PagedArray();

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
         * @param pages
         *
         * @return true
         * @return false
         */
        bool
        attach(long pages);

        /**
         * @brief
         *
         * @param pages
         *
         * @return true
         * @return false
         */
        bool
        detach(long pages);

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
        PageTable m_table;

        /**
         * @brief
         */
        PageAlloc* m_origin;
    };
} // namespace smal

#include <smal/Memory/impl/PagedArray.tpp>

#endif // SMAL_MEMORY_PAGE_ARRAY_HPP
