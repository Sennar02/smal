#ifndef SMAL_MEMORY_LAYOUT_PAGED_LAYOUT_HPP
#define SMAL_MEMORY_LAYOUT_PAGED_LAYOUT_HPP

#include <smal/Memory/Origin/PoolOrigin.hpp>

namespace ma
{
    class PagedLayout
    {
    public:
        /**
         *
         */
        PagedLayout(PoolOrigin& origin, u32 items, u32 scale);

        /**
         *
         */
        u32
        length(u32 scale) const;

        /**
         *
         */
        bool
        resize(u32 items, u32 scale);

        /**
         *
         */
        char&
        find(u32 index, u32 scale) const;

    private:
        /**
         *
         */
        bool
        expand(u32 pages);

        /**
         *
         */
        bool
        shrink(u32 pages);

    protected:
        /**
         *
         */
        PoolOrigin* m_origin;

        /**
         *
         */
        PageTable m_memory;
    };
} // namespace ma

#endif // SMAL_MEMORY_LAYOUT_PAGED_LAYOUT_HPP
