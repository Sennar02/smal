#ifndef SMAL_MEMORY_ARRAY_PAGED_ARRAY_HPP
#define SMAL_MEMORY_ARRAY_PAGED_ARRAY_HPP

#include <smal/Memory/Origin/PoolOrigin.hpp>
#include <smal/Memory/PageTable.hpp>

namespace ma
{
    template <class Type>
    class PagedArray
        : private PageTable
    {
    public:
        static const usize SIZE = sizeof(Type);

    public:
        /**
         *
         */
        PagedArray();

        /**
         *
         *
         * @param origin
         * @param length
         */
        PagedArray(BaseOrigin* origin, usize length = 0);

        /**
         *
         *
         * @param origin
         * @param ptable
         * @param length
         */
        PagedArray(BaseOrigin* origin, PageTable& ptable, usize length = 0);

        /**
         *
         */
        virtual ~PagedArray();

        /**
         *
         *
         * @return
         */
        usize
        length() const;

        /**
         *
         *
         * @param length
         *
         * @return True.
         * @return False.
         */
        bool
        resize(usize length);

        /**
         *
         *
         * @param pages
         *
         * @return True.
         * @return False.
         */
        bool
        attach(usize pages);

        /**
         *
         *
         * @param pages
         *
         * @return True.
         * @return False.
         */
        bool
        detach(usize pages);

        /**
         *
         *
         * @return
         */
        const PageTable&
        ptable() const;

        /**
         *
         *
         * @param index
         *
         * @return
         */
        Type&
        operator[](usize index);

        /**
         *
         *
         * @param index
         *
         * @return
         */
        const Type&
        operator[](usize index) const;

    private:
        /**
         *
         */
        BaseOrigin* m_origin;
    };
} // namespace ma

#include <smal/Memory/impl/PagedArray.tpp>

#endif // SMAL_MEMORY_ARRAY_PAGED_ARRAY_HPP
